
#include "stompclient.h"

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
    m_socket(m_ioService)
{
    // We will use synchronous resolution for now
    tcp::resolver           resolver(m_ioService);
    tcp::resolver::query    query( m_server, std::to_string(m_port) );
    tcp::resolver::iterator iter = resolver.resolve(query);
    
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
        << "destination: /topic/" << topic << "\r\n"
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

    const auto frameType = ReadFirstLine( is );
    switch( frameType )
    {
        case FrameType::Connected:
            m_handler.OnConnected( *this );
            break;
            
        case FrameType::Message:
            ReadMessageContent( is );
            break;
    }
}

StompClient::FrameType StompClient::ReadFirstLine( std::istream& is )
{
    FrameType type = FrameType::Unknown;
    
    std::string line;
    if( std::getline( is, line ) )
    {
        if( line == "CONNECTED" ) return FrameType::Connected;
        if( line == "MESSAGE" ) return FrameType::Message;
    }
    return type;
}

void StompClient::ReadMessageContent( std::istream& is )
{    
    std::string line;    
    while( std::getline( is, line ) && !line.empty() )
    {}
    m_handler.OnMessage( is );
}
