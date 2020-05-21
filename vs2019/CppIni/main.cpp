#include <iostream>
#include "Config.h"

int main()
{
    ini::Config config;
    config.ReadConfig("config.ini");
    std::string HostName = config.ReadString("MYSQL", "HostName", "");
    int Port = config.ReadInt("MYSQL", "Port", 0);
    std::string UserName = config.ReadString("MYSQL", "UserName", "");
    std::string Password = config.ReadString("MYSQL", "Password", "");

    std::cout << "HostName=" << HostName << std::endl;
    std::cout << "Port=" << Port << std::endl;
    std::cout << "UserName=" << UserName << std::endl;
    std::cout << "Password=" << Password << std::endl;
    return 0;
}
