
#ifndef STOMPHANDLER_H
#define STOMPHANDLER_H

#include <string>
#include <fstream>
#include "istomphandler.h"

class ILogger;

class StompHandler : public IStompHandler
{
public:
    StompHandler(   const std::string&  queue,
                    const std::string&  dataDirectory,
                    const ILogger&      logger );
    virtual ~StompHandler();
    
    // IStompHandler
    virtual void OnConnected(StompClient& client);
    virtual void OnMessage( const std::string& message );
    virtual void OnTrace( const std::string& traceDetails );
    virtual void OnFrame( const std::string& frame );

private:
    void ProcessMessageBody( const std::string& bodyContent );

    std::string     m_queue;
    std::string     m_dataDirectory;
    const ILogger&  m_logger;
    bool m_log;
    int  m_fileId;
    std::ofstream m_frameFile;
};

#endif // STOMPHANDLER_H
