
#include "jsonparser.h"

#include <string>
#include <vector>

#include "rapidjson/reader.h"

using namespace rapidjson;

class RapidJSONHandler
{
private:
    std::vector<std::string>    m_context;
    std::string                 m_currentKey;
    JSONParser::ObjectVector&   m_objects;
    JSONParser::Object          m_currentObject;
    
public:
    explicit RapidJSONHandler( JSONParser::ObjectVector& objects )
    : m_context(),
      m_currentKey(),
      m_objects( objects ),
      m_currentObject()
    {}
    
    bool Null() 
    { 
        m_currentKey.clear();
        return true;
    }
    
    bool Bool(bool b)
    { 
        m_currentKey.clear();
        return true;
    }
    
    bool Int(int i)
    {
        m_currentObject[m_currentKey] = std::to_string(i);
        m_currentKey.clear();
        return true;
    }
    
    bool Uint(unsigned u)
    {
        m_currentObject[m_currentKey] = std::to_string(u);
        m_currentKey.clear();
        return true;
    }
    
    bool Int64(int64_t i)
    {
        m_currentKey.clear();
        return true;
    }
    
    bool Uint64(uint64_t u)
    { 
        m_currentKey.clear();
        return true;
    }
    
    bool Double(double d)
    {
        m_currentKey.clear();
        return true;
    }
    
    bool RawNumber(const char* str, SizeType length, bool copy)
    {
        const std::string value( str );
        
        m_currentKey.clear();
        return true;
    }
    
    bool String(const char* str, SizeType length, bool copy)
    {
        const std::string value( str );

        m_currentKey.clear();
        return true;
    }
    
    bool StartObject() 
    {
        m_context.push_back( m_currentKey );
        m_currentKey.clear();
        return true;
    }
    
    bool Key(const char* str, SizeType length, bool copy) 
    {
        m_currentKey = str;
        return true;
    }
    
    bool EndObject(SizeType memberCount)
    {
        m_context.pop_back();
        m_objects.push_back( std::move( m_currentObject ) );
        return true;     
    }
    
    bool StartArray()
    {
        return true;
    }
    
    bool EndArray(SizeType elementCount)
    {
        return true; 
    }
};

JSONParser::JSONParser()
{}

JSONParser::~JSONParser()
{}

bool JSONParser::Parse( const std::string& json,
                        ObjectVector&      objects )
{
    RapidJSONHandler rapidJSONHandler( objects );
    Reader           reader;
    StringStream     ss(json.c_str());
    
    return reader.Parse(ss, rapidJSONHandler);
}
