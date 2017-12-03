
#include "logger.h"

#include <iostream>

namespace
{

std::string TagToString( LogTag tag )
{
    switch( tag )
    {
    case LogTag::StompMessage: return "StompMessage";
    case LogTag::StompTrace: return "StompTrace";
    case LogTag::Misc: return "Misc";
    default: return "<unknown>";
    }
}

}   // Anonymous

Logger::Logger()
{}

Logger::~Logger()
{}

void Logger::Log( LogTag tag, const std::string& message ) const
{
    if( IsTagEnabled( tag ) )
    {
        std::cout << "LOG(" << TagToString( tag ) << "):" << message << std::endl;
    }
}

bool Logger::IsEnabled( LogTag tag ) const
{
    return IsTagEnabled( tag );
}

bool Logger::IsTagEnabled( LogTag tag ) const
{
    return false;
}

