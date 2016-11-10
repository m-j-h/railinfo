
#ifndef STOMPHANDLER_H
#define STOMPHANDLER_H

#include "istomphandler.h"

class StompHandler : public IStompHandler
{
public:
    StompHandler( bool log = false );
    virtual ~StompHandler();
    
    virtual void OnConnected(StompClient& client);
    virtual void OnMessage( std::istream& message );
    virtual void OnTrace( const std::string& traceDetails );
    
private:
    bool m_log;
    int  m_fileId;
};

#endif // STOMPHANDLER_H
