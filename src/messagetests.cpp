
#define BOOST_TEST_MODULE Message Tests
#include <boost/test/included/unit_test.hpp>

#include <string>
#include "message.h"

std::string SampleBody()
{
    return
    "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
    "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
}

std::string SampleBodyWithEmbeddedNul()
{
    return
    "12345678901234567890123456789012345678901234567890123456789012345678901234567890" + 
    std::string( 1, '\0') + 
    "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
}

std::string SampleData(const std::string& body, bool isComplete = true )
{
    int contentLength = body.length();
    if( !isComplete )
    {
        // Expect more data than there is
        contentLength++;
    }
    
    std::ostringstream os;
    os <<
        "MESSAGE\r\n"
        "content-length:" << contentLength << "\r\n"
        "expires:1510684590643\r\n"
        "destination:/queue/D438008888-2222-4444-9628-4de7777fffff\r\n"
        "subscription: 0\r\n"
        "priority:0\r\n"
        "CacheHeaderFilterLevels:201711147151227,\r\n"
        "FilterHeaderLevel:TRAINSTATUS,\r\n"
        "message-id:ID\\cEC2D3-PROD-DB-50817-1508642554538-4\\c1\\c6\\c1\\c1254397054\r\n"
        "persistent:true\r\n"
        "timestamp:1510684290656\r\n"
        "\r\n" <<
        body;

    return os.str() + std::string(1, '\0');
}

BOOST_AUTO_TEST_CASE( CompleteSimpleMessage )
{
    Message m;
    m.AppendData( SampleData( SampleBody() ) );

    std::string result;
    BOOST_REQUIRE( m.GetCompleteMessage( &result ) == true );
    BOOST_REQUIRE( result == SampleBody() );
    BOOST_REQUIRE( m.Content().empty() == true );
}

BOOST_AUTO_TEST_CASE( CompleteMessageWithEmbeddedNul )
{
    Message m;
    m.AppendData( SampleData( SampleBodyWithEmbeddedNul() ) );

    std::string result;
    BOOST_REQUIRE( m.GetCompleteMessage( &result ) == true );
    BOOST_REQUIRE( result == SampleBodyWithEmbeddedNul() );
    BOOST_REQUIRE( m.Content().empty() == true );
}

BOOST_AUTO_TEST_CASE( CompleteSimpleMessageWithExtraDataAtEnd )
{
    const std::string extraData { "abcd" };
    Message m;
    m.AppendData( SampleData( SampleBody() ) );
    m.AppendData( extraData );

    std::string result;
    BOOST_REQUIRE( m.GetCompleteMessage( &result ) == true );
    BOOST_REQUIRE( result == SampleBody() );
    BOOST_REQUIRE( m.Content() == extraData );
}

BOOST_AUTO_TEST_CASE( CompleteMessageWithEmbeddedNulWithExtraDataAtEnd )
{
    const std::string extraData { "abcd" };
    Message m;
    m.AppendData( SampleData( SampleBodyWithEmbeddedNul() ) );
    m.AppendData( extraData );

    std::string result;
    BOOST_REQUIRE( m.GetCompleteMessage( &result ) == true );
    BOOST_REQUIRE( result == SampleBodyWithEmbeddedNul() );
    BOOST_REQUIRE( m.Content() == extraData );
}

BOOST_AUTO_TEST_CASE( IncompleteMessage )
{
    const bool isComplete = false;
    Message m;
    m.AppendData( SampleData( SampleBody(), false ) );

    std::string result;
    BOOST_REQUIRE( m.GetCompleteMessage( &result ) == false );
}

BOOST_AUTO_TEST_CASE( IncompleteMessageWithEmbeddedNull )
{
    const bool isComplete = false;
    Message m;    
    m.AppendData( SampleData( SampleBodyWithEmbeddedNul(), false ) );

    std::string result;
    BOOST_REQUIRE( m.GetCompleteMessage( &result ) == false );
}

