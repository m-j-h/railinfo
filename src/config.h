#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config
{
public:
    explicit Config( const std::string& filename );
    ~Config();
    
    const std::string operator[](const std::string& key);

private:
    const std::string                 m_filename;
    std::map<std::string,std::string> m_config;
};

#endif // CONFIGP_H
