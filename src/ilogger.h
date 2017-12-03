
#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

enum class LogTag
{
    StompMessage,
    StompTrace,
    DumpStompMessages,
    DumpStompFrames,
    Misc
};

class ILogger
{
public:
    virtual ~ILogger() {}

    virtual void Log( LogTag tag, const std::string& message ) const = 0;
    virtual bool IsEnabled( LogTag tag ) const = 0;
};

#endif // ILOGGER_H

