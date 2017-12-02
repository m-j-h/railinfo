
#define BOOST_TEST_MODULE Inflater Tests
#include <boost/test/included/unit_test.hpp>

#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "inflater.h"

// Helpers
void AssertFileOpen( std::ifstream& is, const std::string& filename )
{
    if( !is.is_open() )
    {
        throw std::runtime_error("Failed to open file '" + filename + "'");
    }
}

std::string ReadBinaryFile(const std::string& filename)
{
    std::ifstream fs(filename.c_str(), std::ios::binary );
    AssertFileOpen( fs, filename );

    std::istreambuf_iterator<char> begin( fs );
    std::istreambuf_iterator<char> end;
    std::string content;
    std::copy( begin, end, std::back_inserter( content ) );
    return content;
}

std::string ReadTextLine(const std::string& filename)
{
    std::ifstream fs(filename.c_str());
    AssertFileOpen( fs, filename );

    std::string line;
    std::getline( fs, line );
    return line;
}

// Tests
BOOST_AUTO_TEST_CASE( CompleteMessageWithEmbeddedNulWithExtraDataAtEnd )
{
    std::string compressed = ReadBinaryFile( "./data/data.gz" );
    std::string expected   = ReadTextLine(   "./data/data.xml" );

    Inflater target;
    const std::string result = target.Process(compressed);
    BOOST_REQUIRE( result == expected );
}

