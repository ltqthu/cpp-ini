#ifndef CONFIG_H_
#define CONFIG_H_
#include <string>
#include <map>
#include <iostream>

namespace ini
{
    class Config
    {
    public:
        Config();

        ~Config();

        bool ReadConfig(const std::string& filename);
        std::string ReadString(const char* section, const char* item, const char* default_value);
        int ReadInt(const char* section, const char* item, const int& default_value);
        float ReadFloat(const char* section, const char* item, const float& default_value);
    private:
        bool IsSpaceTab(char c);
        bool IsCommentChar(char c);
        void TrimSpaceTab(std::string& str);
        void ReplaceSpaceTab(std::string& str);
        bool AnalyseLine(const std::string& line, std::string& section, std::string& key, std::string& value);

    private:
        std::map<std::string, std::map<std::string, std::string> > m_settings;
    };
}
#endif

