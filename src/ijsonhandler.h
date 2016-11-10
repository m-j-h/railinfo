#ifndef IJSONHANDLER_H
#define IJSONHANDLER_H

class IJSONHandler
{
public:
    virtual ~IJSONHandler() {}
    
    virtual void StartArray() = 0;
    virtual void EndArray() = 0;
    
    virtual void StartObject( const std::string& name ) = 0;
    virtual void EndObject() = 0;
    
    virtual void String( const std::string& name, const std::string& value ) = 0;
    virtual void Int( const std::string& name, int value ) = 0;
    virtual void UInt( const std::string& name, unsigned int value ) = 0;
};

#endif // IJSONHANDLER_H
