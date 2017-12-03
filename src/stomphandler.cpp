
#include "stomphandler.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "stompclient.h"
#include "inflater/inflater.h"

StompHandler::StompHandler( const std::string& dataDirectory, const std::string& queue )
: m_dataDirectory( dataDirectory ),
  m_queue( queue ),
  m_fileId( 0 ),
  m_frameFile(m_dataDirectory + "/frames_log.txt"),
  m_dumpMessages( false ),
  m_dumpFrames( false ),
  m_dumpTrace( false )
{}

StompHandler::~StompHandler()
{}

void StompHandler::OnConnected(StompClient& client)
{
    client.Subscribe( m_queue );
}

void StompHandler::OnMessage( const std::string& message )
{
    if( m_dumpMessages )
    {
        std::cout << "Logging to file..." << std::endl;

        std::stringstream filename;
        filename << m_dataDirectory << "/" << "msg_" << ++m_fileId << ".txt";
        std::ofstream ofs( filename.str() );
    
        ofs << message << std::endl;
    }

    if( message.find("MESSAGE") == 0 )
    {
        std::cout << "Got MESSAGE" << std::endl;
        const std::string headerEndMarker { "\n\n" };
        const auto headerEndPosition = message.find( headerEndMarker );
        if( headerEndPosition != std::string::npos )
        {
            const auto bodyStartPosition = headerEndPosition + headerEndMarker.length();
            const std::string body = message.substr( bodyStartPosition );

            Inflater inflater;
            const auto result = inflater.Process(body);
            std::cout << result << std::endl;
        }
    }

    if( m_dumpMessages )
    {
        if( m_fileId > 4 )
        {
            m_frameFile.close();
            exit(1);
        }
    }
}

void StompHandler::OnTrace( const std::string& traceDetails )
{
    if( !m_dumpTrace )
    {
        return;
    }

    std::cout << "LOG: " << traceDetails << std::endl;
}

void StompHandler::OnFrame( const std::string& frame )
{
    if( !m_dumpFrames )
    {
        return;
    }

    std::cout << "Logging frame to file..." << std::endl;
    m_frameFile << frame;
}

void StompHandler::EnableMessageDump( bool enable )
{
    m_dumpMessages = enable;
}

void StompHandler::EnableFrameDump( bool enable )
{
    m_dumpFrames = enable;
}

void StompHandler::EnableTrace( bool enable )
{
    m_dumpTrace = enable;
}

