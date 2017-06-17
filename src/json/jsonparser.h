#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>

class IJSONHandler;

class JSONParser
{
public:
    JSONParser();
    ~JSONParser();
    
    bool Parse( const std::string& json,
                IJSONHandler&      handler );
};

#endif // JSONPARSER_H
