
#include "jsonparser.h"

#include <string>
#include <vector>

#include "ijsonhandler.h"

#include "rapidjson/reader.h"

using namespace rapidjson;

class RapidJSONHandler
{
private:
    std::vector<std::string>    m_context;
    std::string                 m_currentKey;
    IJSONHandler&               m_handler;
    JSONParser::ObjectVector&   m_objects;
    JSONParser::Object          m_currentObject;
    
public:
    explicit RapidJSONHandler( IJSONHandler& handler,
                               JSONParser::ObjectVector& objects )
    : m_context(),
      m_currentKey(),
      m_handler( handler ),
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
        m_handler.Int( m_currentKey, i );
        m_currentKey.clear();
        return true;
    }
    
    bool Uint(unsigned u)
    {
        m_handler.UInt( m_currentKey, u );
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
        
        m_handler.String( m_currentKey, value );
        m_currentKey.clear();
        return true;
    }
    
    bool String(const char* str, SizeType length, bool copy)
    {
        const std::string value( str );
        
        m_handler.String( m_currentKey, value );
        m_currentKey.clear();
        return true;
    }
    
    bool StartObject() 
    {
        m_context.push_back( m_currentKey );
        m_handler.StartObject( m_currentKey );
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
        m_handler.EndObject();
        return true;     
    }
    
    bool StartArray()
    {
        m_handler.StartArray();
        return true;
    }
    
    bool EndArray(SizeType elementCount)
    {
        m_handler.EndArray();
        return true; 
    }
};

JSONParser::JSONParser()
{}

JSONParser::~JSONParser()
{}

bool JSONParser::Parse( const std::string& json,
                        IJSONHandler&      handler,
                        ObjectVector&      objects )
{
    RapidJSONHandler rapidJSONHandler( handler, objects );
    Reader           reader;
    StringStream     ss(json.c_str());
    
    return reader.Parse(ss, rapidJSONHandler);
}
