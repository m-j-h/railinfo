
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

    const auto nulCharPos = m_content.find('\0');
    if( nulCharPos == std::string::npos )
    {
        Log("No NUL char found - incomplete message");
        return false;
    }

    const std::string headerEndMarker { "\n\n" };
    const auto headerEndPos = m_content.find( headerEndMarker );
    if( headerEndPos == std::string::npos )
    {
        Log("Got message with no body");
        *message = m_content.substr( 0, nulCharPos );
        m_content.clear();
        return true;
    }
    const auto bodyStartPos = headerEndPos + headerEndMarker.length();

    size_t contentLength = 0;
    if( HasContentLengthHeader( &contentLength ) )
    {
        // The NUL might not be the end of the message
        const auto currentContentLength = m_content.length() - bodyStartPos;
        if( currentContentLength < contentLength )
        {
            Log("ContentLength header indicates incomplete message");
            return false;
        }

        const auto messageLength = bodyStartPos + contentLength + 2;
        *message = m_content.substr( 0, messageLength );
        m_content.erase( 0, messageLength );
        Log("Extracted message based on ContentHeader");
        Log("Excess is '" + m_content + "'");
        return true;
    }
    
    // The NUL defines the end of the message
    *message = m_content.substr( 0, nulCharPos );
    m_content.clear();
    Log("Extracted message based on NUL terminator");
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

