
#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

class ILogger
{
public:
    virtual ~ILogger() {}

    virtual void Log( size_t tag, const std::string& message ) = 0;
};

#endif // ILOGGER_H

