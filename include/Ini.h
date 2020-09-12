#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <iostream>
#include <map>
#include <string>

#include "Tool.h"

std::string IniGetString(const char *szSection, const char *szKey, const char *szDefaultValue);

int IniGetInt(const char *szSection, const char *szKey, const int &szDefaultValue);

double IniGetDouble(const char *szSection, const char *szKey, const double &szDefaultValue);

class Ini {
public:
    static Ini *Instance() { return &m_instance; }

    Ini();

    ~Ini();

    // 读取配置文件
    bool ReadConfig(const std::string &filename);

    // 读取字符串
    std::string GetString(const char *szSection, const char *szKey, const char *szDefaultValue);

    // 读取整型
    int GetInt(const char *szSection, const char *szKey, const int &nDefaultValue);

    // 读取浮点型
    double GetDouble(const char *szSection, const char *szKey, const double &dDefaultValue);

private:
    // 判断是否是space或者tab
    bool IsSpaceTab(char c);
    // 判断是否是备注标识符#
    bool IsComment(char c);
    // 删除首尾的空格
    void Trim(std::string &str);
    // 从一行中提取配置信息
    bool ExtractConfig(const std::string &strLine, std::string &strSection, std::string &strKey, std::string &strValue);

private:
    std::string m_strIniName;
    std::map<std::string, std::map<std::string, std::string>> m_settings;

public:
    static Ini m_instance;
};
#endif
