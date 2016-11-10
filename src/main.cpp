
#include <cstdlib>
#include <iostream>

#include "config.h"
#include "stompclient.h"
#include "stomphandler.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return EXIT_FAILURE;
        }
        
        Config config( argv[1] );
        const auto hostname = config["hostname"];
        const auto port     = static_cast<unsigned int>(std::stoi(config["port"]));
        const auto username = config["username"];
        const auto password = config["password"];
        
        StompHandler sh(true);
        StompClient sc( hostname,
                        port,
                        username,
                        password,
                        sh );
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
