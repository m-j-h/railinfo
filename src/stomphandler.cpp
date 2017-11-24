
#include "stomphandler.h"
#include "stompclient.h"

#include <iostream>
#include <fstream>
#include <sstream>

StompHandler::StompHandler( const std::string& dataDirectory, const std::string& queue )
: m_dataDirectory( dataDirectory ),
  m_queue( queue ),
  m_fileId( 0 ),
  m_frameFile(m_dataDirectory + "/frames_log.txt") 
{}

StompHandler::~StompHandler()
{}

void StompHandler::OnConnected(StompClient& client)
{
    client.Subscribe( m_queue );
}

void StompHandler::OnMessage( std::istream& message )
{
    std::cout << "Logging to file..." << std::endl;

    std::stringstream filename;
    filename << m_dataDirectory << "/" << "msg_" << ++m_fileId << ".json";
    std::ofstream ofs( filename.str() );
    
    std::string line;
    while( std::getline( message, line ) )
    {
        ofs << line << std::endl;
    }
}

void StompHandler::OnMessage( const std::string& message )
{
    std::cout << "Logging to file..." << std::endl;

    std::stringstream filename;
    filename << m_dataDirectory << "/" << "msg_" << ++m_fileId << ".txt";
    std::ofstream ofs( filename.str() );
    
    ofs << message << std::endl;

    if( m_fileId > 4 )
    {
        m_frameFile.close();
        exit(1);
    }
}

void StompHandler::OnTrace( const std::string& traceDetails )
{
    std::cout << "LOG: " << traceDetails << std::endl;
}

void StompHandler::OnFrame( const std::string& frame )
{
    std::cout << "Logging frame to file..." << std::endl;

    m_frameFile << frame;
}

