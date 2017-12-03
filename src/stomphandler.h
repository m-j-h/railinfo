
#ifndef STOMPHANDLER_H
#define STOMPHANDLER_H

#include <string>
#include <fstream>
#include "istomphandler.h"

class StompHandler : public IStompHandler
{
public:
    StompHandler( const std::string& dataDirectory, const std::string& queue );
    virtual ~StompHandler();
    
    // IStompHandler
    virtual void OnConnected(StompClient& client);
    virtual void OnMessage( const std::string& message );
    virtual void OnTrace( const std::string& traceDetails );
    virtual void OnFrame( const std::string& frame );
    
    void EnableMessageDump( bool enable );
    void EnableFrameDump( bool enable );
    void EnableTrace( bool enable );

private:
    std::string m_dataDirectory;
    std::string m_queue;
    bool m_log;
    int  m_fileId;
    std::ofstream m_frameFile;
    bool m_dumpMessages;
    bool m_dumpFrames;
    bool m_dumpTrace;
};

#endif // STOMPHANDLER_H
