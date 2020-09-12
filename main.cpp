#include <iostream>

#include "include/Ini.h"

int main() {
    std::string ip = Ini::Instance()->GetString("Netsetting", "IP", "");

    printf("%s:%d [Netsetting] IP: %s\n", __FILE__, __LINE__, ip.c_str());

    int port = Ini::Instance()->GetInt("Netsetting", "Port", 0);
    printf("%s:%d [Netsetting] Port: %d\n", __FILE__, __LINE__, port);

    std::string mysql_ip = Ini::Instance()->GetString("MySQL", "IP", "");

    printf("%s:%d [MySQL] IP: %s\n", __FILE__, __LINE__, mysql_ip.c_str());

    int mysql_port = Ini::Instance()->GetInt("MySQL", "Port", 0);
    printf("%s:%d [MySQL] Port: %d\n", __FILE__, __LINE__, mysql_port);

    std::string mysql_username = Ini::Instance()->GetString("MySQL", "Username", "");
    printf("%s:%d [MySQL] Username: %s\n", __FILE__, __LINE__, mysql_username.c_str());

    std::string mysql_password = Ini::Instance()->GetString("MySQL", "Password", "");
    printf("%s:%d [MySQL] Password: %s\n", __FILE__, __LINE__, mysql_password.c_str());

    return 0;
}
