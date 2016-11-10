
#include "stomphandler.h"
#include "stompclient.h"

#include <iostream>
#include <fstream>
#include <sstream>

StompHandler::StompHandler( bool log )
: m_log( log ),
  m_fileId( 0 )
{}

StompHandler::~StompHandler()
{}

void StompHandler::OnConnected(StompClient& client)
{
    client.Subscribe("TRAIN_MVT_EF_TOC");
}

void StompHandler::OnMessage( std::istream& message )
{
    if( m_log )
    {
        std::cout << "Logging to file..." << std::endl;

        std::stringstream filename;
        filename << "msg_" << ++m_fileId << ".json";
        std::ofstream ofs( filename.str() );
        
        std::string line;
        while( std::getline( message, line ) )
        {
            ofs << line << std::endl;
        }
    }
    else
    {    
        std::string line;
        while( std::getline( message, line ) )
        {
            std::cout << line << std::endl;
        }
        std::cout << "----" << std::endl;
    }
}

void StompHandler::OnTrace( const std::string& traceDetails )
{
    std::cout << "LOG: " << traceDetails << std::endl;
}
