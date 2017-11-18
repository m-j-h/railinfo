
#ifndef STOMPHANDLER_H
#define STOMPHANDLER_H

#include <string>
#include "istomphandler.h"

class StompHandler : public IStompHandler
{
public:
    StompHandler( const std::string& dataDirectory, const std::string& queue );
    virtual ~StompHandler();
    
    virtual void OnConnected(StompClient& client);
    virtual void OnMessage( std::istream& message );
    virtual void OnMessage( const std::string& message );
    virtual void OnTrace( const std::string& traceDetails );
    
private:
    std::string m_dataDirectory;
    std::string m_queue;
    bool m_log;
    int  m_fileId;
};

#endif // STOMPHANDLER_H
