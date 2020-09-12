#include <iostream>

#include "include/Config.h"

int main()
{
    ini::Config config;
    config.ReadConfig("Config.ini");

    std::string strIP = config.GetString("Netsetting", "IP", "");
    std::string strPort = config.GetString("Netsetting", "Port", "");
    std::cout << "IP=" << strIP << std::endl;
    std::cout << "Port=" << strPort << std::endl;

    std::string HostName = config.GetString("MySQL", "Hostname", "");
    int Port = config.GetInt("MySQL", "Port", 0);
    std::string UserName = config.GetString("MySQL", "Username", "");
    std::string Password = config.GetString("MySQL", "Password", "");

    std::cout << "HostName=" << HostName << std::endl;
    std::cout << "Port=" << Port << std::endl;
    std::cout << "UserName=" << UserName << std::endl;
    std::cout << "Password=" << Password << std::endl;

    return 0;
}
