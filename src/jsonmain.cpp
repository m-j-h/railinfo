
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#include "jsonparser.h"
#include "ijsonhandler.h"

class Logger : public IJSONHandler
{
public:
    Logger()
    {}
    
    virtual ~Logger()
    {}
    
    virtual void StartArray()
    {
        std::cout << "StartArray" << std::endl;
    }
    
    virtual void EndArray()
    {
        std::cout << "EndArray" << std::endl;
    }
    
    virtual void StartObject( const std::string& name )
    {
        std::cout << "StartObject '" << name << "'" << std::endl;
    }
    
    virtual void EndObject()
    {
        std::cout << "EndObject" << std::endl;
    }

    virtual void String( const std::string& name, const std::string& value )
    {
        std::cout << "String: name='" << name << "' value='" << value << "'" << std::endl;
    }
    
    virtual void Int( const std::string& name, int value )
    {
        std::cout << "Int: name='" << name << "' value='" << value << "'" << std::endl;
    }
    
    virtual void UInt( const std::string& name, unsigned int value )
    {
        std::cout << "UInt: name='" << name << "' value='" << value << "'" << std::endl;
    }
};

int main(int argc, char** argv) 
{
    if( argc < 2 )
    {
        std::cout << "usage: json <file>" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream jsonFile(argv[1]);
    std::string json;
    std::getline( jsonFile, json );
    
    JSONParser parser;
    Logger logger;
    parser.Parse( json, logger );
    
    return 0;
}
