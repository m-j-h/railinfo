#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "ilogger.h"

class Message
{
public:
    explicit Message( const ILogger& logger );
    ~Message();

    void AppendData( const std::string& data );
    bool GetCompleteMessage( std::string* message );
    std::string Content() const;

private:
    bool HasContentLengthHeader( size_t* cl ) const;
    void Log( const std::string& message );

    std::string     m_content;
    size_t          m_bodyStart;
    size_t          m_bodyLength;
    const ILogger&  m_logger;
};

#endif // MESSAGE_H

