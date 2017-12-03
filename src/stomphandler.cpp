
#include "stomphandler.h"

#include <fstream>
#include <iostream>

#include "stompclient.h"
#include "inflater/inflater.h"

namespace 
{

std::string ExtractMessageBody( const std::string& message )
{
    if( message.find("MESSAGE") != 0 )
    {
        return "";
    }

    const std::string headerEndMarker { "\n\n" };
    const auto headerEndPosition = message.find( headerEndMarker );
    if( headerEndPosition == std::string::npos )
    {
        return "";
    }

    const auto bodyStartPosition = headerEndPosition + headerEndMarker.length();
    return message.substr( bodyStartPosition );
}

}   // Anonymous

StompHandler::StompHandler( const std::string&  queue,
                            const std::string&  dataDirectory,
                            const ILogger&      logger )
: m_queue( queue ),
  m_dataDirectory( dataDirectory ),
  m_logger( logger ),
  m_fileId( 0 ),
  m_frameFile(m_dataDirectory + "/frames_log.txt")
{}

StompHandler::~StompHandler()
{}

void StompHandler::OnConnected(StompClient& client)
{
    client.Subscribe( m_queue );
}

void StompHandler::OnMessage( const std::string& message )
{
    if( m_logger.IsEnabled( LogTag::DumpStompMessages ) )
    {
        std::stringstream filename;
        filename << m_dataDirectory << "/" << "msg_" << ++m_fileId << ".txt";
        std::ofstream ofs( filename.str() );
        ofs << message << std::endl;
    }

    const auto messageBody = ExtractMessageBody( message );
    if( !messageBody.empty() )
    {
        ProcessMessageBody( messageBody );
    }
}

void StompHandler::OnTrace( const std::string& traceDetails )
{
    m_logger.Log( LogTag::StompTrace, traceDetails );
}

void StompHandler::OnFrame( const std::string& frame )
{
    if( !m_logger.IsEnabled( LogTag::DumpStompFrames ) )
    {
        return;
    }

    m_frameFile << frame;
}

void StompHandler::ProcessMessageBody( const std::string& bodyContent )
{
    Inflater inflater;
    const auto result = inflater.Process(bodyContent);
    std::cout << result << std::endl;
}

