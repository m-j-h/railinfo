
#include "config.h"

#include <fstream>
#include <iostream>

namespace
{
    
std::string RemoveSpaces( const std::string& s )
{
    return s;
}

}

Config::Config( const std::string& filename )
: m_filename( filename ),
  m_config()
{
    std::ifstream ifs( m_filename );
    
    std::string line;
    while( std::getline( ifs, line ) )
    {
        const auto index = line.find(':');
        if( index != std::string::npos )
        {
            std::string key = line.substr(0, index);
            
            std::string value;
            if( index < line.length() )
            {
                value = line.substr(index+1);
            }
            m_config.insert( std::make_pair( key, value ) );
            std::cout << "Config[" << key << "] = " << "'" << value << "'" << std::endl;
        }
    }
}

Config::~Config()
{}

const std::string Config::operator[](const std::string& key)
{
    return m_config[key];
}
