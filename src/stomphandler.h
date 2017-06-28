
#ifndef STOMPHANDLER_H
#define STOMPHANDLER_H

#include <string>
#include "istomphandler.h"

class StompHandler : public IStompHandler
{
public:
    StompHandler( const std::string& dataDirectory );
    virtual ~StompHandler();
    
    virtual void OnConnected(StompClient& client);
    virtual void OnMessage( std::istream& message );
    virtual void OnTrace( const std::string& traceDetails );
    
private:
    std::string m_dataDirectory;
    bool m_log;
    int  m_fileId;
};

#endif // STOMPHANDLER_H
