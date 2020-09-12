#include "Tool.h"

std::string GetPathAndExecutableName() {
    char szPathName[1024] = {0};
    if (readlink("/proc/self/exe", szPathName, 1024) <= 0) {
        return "";
    }
    return szPathName;
}

std::string GetPath() {
    std::string strPathName = GetPathAndExecutableName();
    std::string::size_type pos = strPathName.find_last_of("/");
    return strPathName.substr(0, pos);
}
std::string GetExecutableName() {
    std::string strPathName = GetPathAndExecutableName();
    std::string::size_type pos = strPathName.find_last_of("/");
    return strPathName.substr(pos + 1);
}
