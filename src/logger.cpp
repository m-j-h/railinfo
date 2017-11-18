
#include "logger.h"

#include <iostream>

Logger::Logger()
{}

Logger::~Logger()
{}

void Logger::Log( size_t tag, const std::string& message )
{
    std::cout << "LOG(" << tag << "):" << message << std::endl; 
}

