
#ifndef ISTOMPHANDLER_H
#define ISTOMPHANDLER_H

#include <iosfwd>
#include <string>

class StompClient;

class IStompHandler
{
public:
    virtual ~IStompHandler() {};
    virtual void OnConnected(StompClient& client) = 0;
    virtual void OnMessage( std::istream& message ) = 0;
    virtual void OnMessage( const std::string& message ) = 0;
    virtual void OnTrace( const std::string& traceDetails ) = 0;
};

#endif // ISTOMPHANDLER_H
