
#include "stompclient.h"
#include <iostream>

using boost::asio::ip::tcp;

StompClient::StompClient(   const std::string& server,
                            unsigned int       port,
                            const std::string& username,
                            const std::string& password,
                            IStompHandler&     handler )
:   m_server( server ),
    m_port( port ),
    m_username( username ),
    m_password( password ),
    m_handler( handler ),
    m_ioService(),
    m_socket(m_ioService),
    m_currentMessage(),
    m_message(),
    m_logger()
{
    // We will use synchronous resolution for now
    tcp::resolver           resolver(m_ioService);
    tcp::resolver::query    query( m_server, std::to_string(m_port) );
    tcp::resolver::iterator iter = resolver.resolve(query);
    
    //m_message.SetLogger( &m_logger );

    Connect( iter );
    
    // For now we run our service loop here
    m_ioService.run();
}

StompClient::~StompClient()
{}

void StompClient::Subscribe( const std::string& topic )
{
    std::ostringstream os;
    os  << "SUBSCRIBE\r\n"
        << "id: 0\r\n"
        << "destination: /queue/" << topic << "\r\n"
        << "ack: auto\r\n"
        << "\r\n"
        << '\0';

    SendFrame( os.str() );
}

void StompClient::Connect( tcp::resolver::iterator endpointIterator )
{
    boost::asio::async_connect(
        m_socket,
        endpointIterator,
        [this](boost::system::error_code ec, tcp::resolver::iterator)
        {
            if (!ec)
            {
                m_handler.OnTrace( "Connected to server" );
                ConnectToStomp();
            }
        });
}

void StompClient::ConnectToStomp()
{
    std::ostringstream os;
    os  <<  "CONNECT\r\n"
        <<  "accept-version: 1.2\r\n"
        <<  "login: " << m_username << "\r\n" 
        <<  "passcode: " << m_password << "\r\n"
        <<  "\r\n"
        <<  '\0';

    ReceiveFrame();
    SendFrame( os.str() );
}

void StompClient::SendFrame( const std::string& frame )
{
    std::shared_ptr<std::string> buffer( new std::string(frame) );
    
    boost::asio::async_write(
        m_socket,
        boost::asio::buffer(*buffer),
        [this, buffer]( boost::system::error_code ec, std::size_t length )
        {
            if( !ec )
            {
                m_handler.OnTrace( "Sent frame" );
            }
        } );
}

void StompClient::ReceiveFrame()
{
    std::shared_ptr<boost::asio::streambuf> buffer( new boost::asio::streambuf() );
    
    m_handler.OnTrace("Waiting for frame");
    boost::asio::async_read_until(
        m_socket,
        *buffer,
        '\0',
        [this, buffer]( boost::system::error_code ec, std::size_t length )
        {
            if( !ec )
            {
                m_handler.OnTrace( "Received frame" );
                ProcessFrame( *buffer, length );
            }
            ReceiveFrame();
        } );
}

void StompClient::ProcessFrame(boost::asio::streambuf& buffer, std::size_t length)
{
    std::istream is(&buffer);
     
    std::cout << "Frame size: " << length << std::endl;
    std::istreambuf_iterator<char> eos;
    std::string frame( std::istreambuf_iterator<char>( is ), eos);
    std::cout << "Read from frame: " << frame.length() << std::endl;
    
    m_handler.OnFrame( frame );
    m_message.AppendData( frame );

    std::string result;
    if( m_message.GetCompleteMessage( &result ) )
    {
        if( result.find( "CONNECTED" ) == 0 )
        {
            m_handler.OnConnected( *this );
        }

        m_handler.OnMessage( result );
    }
}

size_t StompClient::GetContentLength() const
{
    const std::string header { "content-length:" };
    const auto pos = m_currentMessage.find( header );
    if( pos == std::string::npos )
    {
        return 0;
    }

    const auto tagEndPos = pos + header.length();
    const auto valueEnd = m_currentMessage.find_first_of("\r\n", tagEndPos);
    const std::string s( m_currentMessage, tagEndPos, valueEnd - tagEndPos );
    std::cout << "S = " << s << std::endl;
    return std::stoi(s);
}

