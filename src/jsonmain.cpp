
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#include "jsonparser.h"
#include "ijsonhandler.h"

//#include "rapidjson/reader.h"

/*
using namespace rapidjson;
using namespace std;

struct MyHandler
{
    std::vector<std::string>    m_context;
    std::string                 m_currentKey;
    bool                        m_trace;
    
    MyHandler()
    :   m_context(),
        m_currentKey(),
        m_trace(false)
    {}
    
    std::string Scope() 
    {
        std::string scope;
        
        for( auto c : m_context )
        {
            scope += c;
            scope += '.';
        }
        scope += m_currentKey;
        return scope;
    }
    
    bool Null() 
    { 
        cout << Scope() << " Null()" << endl;
        m_currentKey.clear();
        return true;
    }
    
    bool Bool(bool b)
    { 
        cout << Scope() << " Bool(" << boolalpha << b << ")" << endl; 
        m_currentKey.clear();
        return true;
    }
    
    bool Int(int i)
    {
        cout << Scope() << " Int(" << i << ")" << endl; 
        m_currentKey.clear();
        return true;
    }
    
    bool Uint(unsigned u)
    {
        cout << Scope() << " Uint(" << u << ")" << endl;
        m_currentKey.clear();
        return true;
    }
    
    bool Int64(int64_t i)
    {
        cout << Scope() << " Int64(" << i << ")" << endl;
        m_currentKey.clear();
        return true;
    }
    
    bool Uint64(uint64_t u)
    { 
        cout << Scope() << " Uint64(" << u << ")" << endl;
        m_currentKey.clear();
        return true;
    }
    
    bool Double(double d)
    {
        cout << Scope() << " Double(" << d << ")" << endl;
        m_currentKey.clear();
        return true;
    }
    
    bool RawNumber(const char* str, SizeType length, bool copy)
    { 
        cout << Scope() << " Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        m_currentKey.clear();
        return true;
    }
    
    bool String(const char* str, SizeType length, bool copy)
    { 
        cout << Scope() << " String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        m_currentKey.clear();
        return true;
    }
    
    bool StartObject() 
    {
        m_context.push_back( m_currentKey );
        m_currentKey.clear();
        cout << Scope() << " StartObject()" << endl;

        if( m_trace )
        {
            cout << "StartObject()" << endl;
        }
        return true;
    }
    
    bool Key(const char* str, SizeType length, bool copy) 
    {
        m_currentKey = str;
        
        if( m_trace )
        {
            cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        }
        return true;
    }
    
    bool EndObject(SizeType memberCount)
    {
        m_context.pop_back();
        
        if( m_trace )
        {
            cout << "EndObject(" << memberCount << ")" << endl;
        }
        return true;     
    }
    
    bool StartArray()
    {
        if( m_trace )
        {
            cout << "StartArray()" << endl;
        }
        return true;
    }
    
    bool EndArray(SizeType elementCount)
    {
        if( m_trace )
        {
            cout << "EndArray(" << elementCount << ")" << endl;
        }
        return true; 
    }
};
*/

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
