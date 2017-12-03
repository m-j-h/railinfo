
#ifndef LOGGER_H
#define LOGGER_H

#include "ilogger.h"

class Logger : public ILogger
{
public:
    Logger();
    virtual ~Logger();

    virtual void Log( LogTag tag, const std::string& message ) const;
    virtual bool IsEnabled( LogTag tag ) const;

private:
    bool IsTagEnabled( LogTag tag ) const;
};

#endif // LOGGER_H

