
#define BOOST_TEST_MODULE Inflater Tests
#include <boost/test/included/unit_test.hpp>

#include <string>
#include "inflater.h"

BOOST_AUTO_TEST_CASE( CompleteMessageWithEmbeddedNulWithExtraDataAtEnd )
{
    Inflater target;
    const std::string source = "Some invalid data";
    const std::string result = target.Process(source);
    BOOST_REQUIRE( result == source );
}

