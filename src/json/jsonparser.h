#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <map>
#include <vector>

class IJSONHandler;

class JSONParser
{
public:
    using Object = std::map<std::string,std::string>;
    using ObjectVector = std::vector<Object>;

    JSONParser();
    ~JSONParser();
    
    bool Parse( const std::string& json,
                IJSONHandler&      handler,
                ObjectVector&      objects );
};

#endif // JSONPARSER_H
