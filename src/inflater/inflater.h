#ifndef INFLATER_H
#define INFLATER_H

#include <string>

class Inflater
{
public:
    Inflater();
    ~Inflater();
    
    std::string Process( const std::string& source );
};

#endif // INFLATER_H

