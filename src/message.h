#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "ilogger.h"

class Message
{
public:
    Message();
    ~Message();

    void AppendData( const std::string& data );
    bool GetCompleteMessage( std::string* message );
    std::string Content() const;

    void SetLogger( ILogger* logger );

private:
    bool HasContentLengthHeader( size_t* cl ) const;
    void Log( const std::string& message );

    std::string m_content;
    size_t      m_bodyStart;
    size_t      m_bodyLength;
    ILogger*    m_logger;
};

#endif // MESSAGE_H

