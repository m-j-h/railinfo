
#include "message.h"

Message::Message()
: m_content(),
  m_bodyStart(std::string::npos),
  m_bodyLength(std::string::npos)
{}

Message::~Message()
{}

void Message::AppendData( const std::string& data )
{
    m_content += data;
}

bool Message::GetCompleteMessage( std::string* message )
{
    Log("++GetCompleteMessage");
    if( m_bodyStart == std::string::npos )
    {
        Log("Finding start of body");
        // Find start of body
        const std::string headerEndMarker { "\r\n\r\n" };
        const auto headerEndPos = m_content.find( headerEndMarker );
        if( headerEndPos == std::string::npos )
        {
            // We haven't even seen the start of the bodt yet - so no content
            Log("Start of body not found");
            return false;
        }
        Log("Set start of body");
        m_bodyStart = headerEndPos + headerEndMarker.length();
    }

    if( m_bodyLength == std::string::npos )
    {
        // Find out how much data we have
        size_t contentLength = 0;
        if( HasContentLengthHeader( &contentLength ) )
        {
            Log("Found Content Length header");
            const auto currentContentLength = m_content.length() - m_bodyStart;
            if( currentContentLength < contentLength )
            {
                // We don't have all the body content yet
                Log("Have less data than specified by Content Length");
                return false;
            }
            m_bodyLength = contentLength;
        }
        else
        {
            Log("No Content Length Header found");
            const auto terminatingNullPos = m_content.find('\0');
            if( terminatingNullPos == std::string::npos )
            {
                // We don't have all the data yet
                Log("No Nul terminator found - don't have complete message");
                return false;
            }
            Log("Set body length");
            m_bodyLength = terminatingNullPos - m_bodyStart;
        }
    }

    Log("Have complete message - setting result");

    // If we get here then we have the entire body content and know where this is
    *message = m_content.substr( m_bodyStart, m_bodyLength );

    // Consume the content we're returning leaving any excess
    m_content = m_content.substr( m_bodyStart + m_bodyLength );
    return true;
}

std::string Message::Content() const
{
    return m_content;
}

void Message::SetLogger( ILogger* logger )
{
    m_logger = logger;
}

bool Message::HasContentLengthHeader( size_t* cl ) const
{
    const std::string headerTag { "content-length:" };
    const auto tagPos = m_content.find( headerTag );
    if( tagPos == std::string::npos )
    {
        return false;
    }

    const auto tagEndPos = tagPos + headerTag.length();
    const auto valueEndPos = m_content.find_first_of("\r\n", tagEndPos);
    if( valueEndPos == std::string::npos )
    {
        return false;
    }

    const std::string value( m_content, tagEndPos, valueEndPos - tagEndPos );
    *cl = std::stoi(value);
    return true;
}

void Message::Log( const std::string& message )
{
    if( m_logger != nullptr )
    {
        m_logger->Log( 0, message );
    }
}

