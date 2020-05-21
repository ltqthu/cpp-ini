#ifndef RR_CONFIG_H_
#define RR_CONFIG_H_
#include <string>
#include <map>

namespace ini 
{
    class Config
    {
    public:
        Config()
        {
        }
        ~Config()
        {
        }
        bool ReadConfig(const std::string& filename);
        std::string ReadString(const char* section, const char* item, const char* default_value);
        int ReadInt(const char* section, const char* item, const int& default_value);
        float ReadFloat(const char* section, const char* item, const float& default_value);
    private:
        // 判断是否是space或者tab
        bool IsSpaceTab(char c);
        // 判断是否是备注标识符#
        bool IsCommentChar(char c);
        void TrimSpaceTab(std::string& str);
        void ReplaceSpaceTab(std::string& str);
        bool AnalyseLine(const std::string& line, std::string& section, std::string& key, std::string& value);

    private:
        //std::map<std::string, std::string> settings_;
        std::map<std::string, std::map<std::string, std::string> >m_settings;
    };
}
#endif

