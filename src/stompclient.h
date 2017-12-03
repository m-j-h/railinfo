#ifndef STOMP_H
#define STOMP_H

#include <string>
#include <boost/asio.hpp>

#include "istomphandler.h"
#include "message.h"
#include "logger.h"

class ILogger;

class StompClient
{
public:
    StompClient( const std::string& server,
                 unsigned int       port,
                 const std::string& username,
                 const std::string& password,
                 IStompHandler&     handler,
                 const ILogger&     logger );
    ~StompClient();
    
    void Subscribe( const std::string& topic );
    
private:
    enum class FrameType
    {
        Unknown,
        Connected,
        Message
    };
    
    void Connect( boost::asio::ip::tcp::resolver::iterator endpointIterator );
    void ConnectToStomp();
    void SendFrame( const std::string& frame );
    void ReceiveFrame();
    void ProcessFrame(boost::asio::streambuf& buffer, std::size_t length);
    
    const std::string   m_server;
    const unsigned int  m_port;
    const std::string   m_username;
    const std::string   m_password;
    
    IStompHandler&                  m_handler;
    boost::asio::io_service         m_ioService;
    boost::asio::ip::tcp::socket    m_socket;
    std::string                     m_currentMessage;
    Message                         m_message;
    const ILogger&                  m_logger;
};

#endif // STOMP_H
