#include <iostream>
#include "Config.h"

int main()
{
    ini::Config config;
    config.ReadConfig("config.ini");

    std::string strIP = config.ReadString("Netsetting", "IP", "");
    std::string strPort = config.ReadString("Netsetting", "Port", "");
    std::cout << "IP=" << strIP << std::endl;
    std::cout << "Port=" << strPort << std::endl;

    std::string HostName = config.ReadString("MySQL", "Hostname", "");
    int Port = config.ReadInt("MYSQL", "Port", 0);
    std::string UserName = config.ReadString("MySQL", "Username", "");
    std::string Password = config.ReadString("MySQL", "Password", "");



    std::cout << "HostName=" << HostName << std::endl;
    std::cout << "Port=" << Port << std::endl;
    std::cout << "UserName=" << UserName << std::endl;
    std::cout << "Password=" << Password << std::endl;
    return 0;
}
