
#ifndef LOGGER_H
#define LOGGER_H

#include "ilogger.h"

class Logger : public ILogger
{
public:
    Logger();
    virtual ~Logger();

    virtual void Log( size_t tag, const std::string& message );
};

#endif // LOGGER_H

