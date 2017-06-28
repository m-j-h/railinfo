
#define BOOST_TEST_MODULE JSON Parser Tests
#include <boost/test/included/unit_test.hpp>

#include "jsonparser.h"

BOOST_AUTO_TEST_CASE( firstTest )
{
    const std::string           json = "{ \"a\" : 1, \"b\" : 2 }";
    JSONParser                  target;
    JSONParser::ObjectVector    objects;
    
    const bool ok = target.Parse(json, objects);
    
    BOOST_REQUIRE(ok);
    BOOST_REQUIRE(objects.size() == 1);
    
    auto objectOne = objects[0];
    BOOST_REQUIRE_EQUAL(objectOne.size(), 2);
    BOOST_REQUIRE(objectOne["a"] == "1");
    BOOST_REQUIRE(objectOne["b"] == "2");
}
