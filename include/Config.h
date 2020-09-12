#ifndef RR_CONFIG_H_
#define RR_CONFIG_H_
#include <string>
#include <map>

namespace ini
{
    class Config
    {
    public:
        Config();

        ~Config();

        // 读取配置文件
        bool ReadConfig(const std::string& filename);

        // 读取字符串
        std::string GetString(const char* szSection, const char* szKey, const char* szDefaultValue);

        // 读取整型
        int GetInt(const char* szSection, const char* szKey, const int& szDefaultValue);

        // 读取浮点型
        double GetDouble(const char* szSection, const char* szKey, const double& szDefaultValue);

    private:
        // 判断是否是space或者tab
        bool IsSpaceTab(char c);
        // 判断是否是备注标识符#
        bool IsComment(char c);
        // 删除首尾的空格
        void Trim(std::string& str);
        // 从一行中提取配置信息
        bool ExtractConfig(const std::string& strLine, std::string& strSection, std::string& strKey, std::string& strValue);

    private:
        std::map<std::string, std::map<std::string, std::string> >m_settings;
    };
}
#endif
