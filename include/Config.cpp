#include "Config.h"
#include <fstream>

namespace ini
{
    Config::Config()
    {
    }

    Config::~Config()
    {
        m_settings.clear();
    }

    bool Config::IsSpaceTab(char c)
    {
        if (' ' == c || '\t' == c)
        {
            return true;
        }
        return false;
    }

    bool Config::IsComment(char c)
    {
        switch (c)
        {
        case '#':
            return true;
        default:
            return false;
        }
    }

    void Config::Trim(std::string &str)
    {
        // 判断是否为空
        if (str.empty())
        {
            return;
        }

        // 从左到右判断，如果都是空格，则返回空字符串
        size_t i, nStartPos, nEndPos;
        for (i = 0; i < str.size(); ++i)
        {
            if (!IsSpaceTab(str[i]))
            {
                break;
            }
        }
        if (i == str.size())
        {
            str = "";
            return;
        }
        nStartPos = i; // 从左到右，第一个非空字符的位置

        // 从右到左判断，如果都是空格，则返回空字符串
        for (i = str.size() - 1; i >= 0; --i)
        {
            if (!IsSpaceTab(str[i]))
            {
                break;
            }
        }
        nEndPos = i; // 从右到左，第一个非空字符串的位置

        str = str.substr(nStartPos, nEndPos - nStartPos + 1);
    }

    bool Config::ExtractConfig(const std::string &strLine, std::string &strSection, std::string &strKey, std::string &strValue)
    {
        // 安全检查
        if (strLine.empty())
        {
            return false;
        }

        size_t nPos;                         // 移动的位置
        size_t nStartPos = 0;                // 起始位置
        size_t nEndPos = strLine.size() - 1; // 结束位置
        size_t nStartPosOfBracket;           // 括号开始的位置
        size_t nEndPosOfBracket;             // 括号结束的位置

        // 行中包含#
        if ((nPos = strLine.find("#")) != std::string::npos)
        {
            // 第一个字符是#，则整行都是注释
            if (0 == nPos)
            {
                return false;
            }
            // #不是首字符
            nEndPos = nPos - 1;
        }

        // 提取出section
        if (((nStartPosOfBracket = strLine.find("[")) != std::string::npos) && ((nEndPosOfBracket = strLine.find("]"))) != std::string::npos)
        {
            strSection = strLine.substr(nStartPosOfBracket + 1, nEndPosOfBracket - 1);
            return true;
        }

        // 提取出去掉#注释的key=value
        std::string strNewLine = strLine.substr(nStartPos, nStartPos + 1 - nEndPos);
        // 没找到等号
        if ((nPos = strNewLine.find('=')) == std::string::npos)
        {
            return false;
        }

        strKey = strNewLine.substr(0, nPos);
        strValue = strNewLine.substr(nPos + 1, nEndPos + 1 - (nPos + 1));
        Trim(strKey);
        if (strKey.empty())
        {
            return false;
        }

        Trim(strValue);
        if (nPos = strValue.find("\r") != std::string::npos)
        {
            if ((nPos = strValue.find("\r")) > 0)
            {
                strValue.replace(nPos, 1, "");
            }
        }

        if (nPos = strValue.find("\n") != std::string::npos)
        {
            if ((nPos = strValue.find("\n")) > 0)
            {
                strValue.replace(nPos, 1, "");
            }
        }

        return true;
    }

    bool Config::ReadConfig(const std::string &strFilename)
    {
        // 清空设置
        m_settings.clear();

        // 读取文件
        std::ifstream inFile(strFilename.c_str());
        if (!inFile)
        {
            return false;
        }

        std::string strLine, strSection, strKey, strValue;
        std::map<std::string, std::string> mapKeyValue;
        std::map<std::string, std::map<std::string, std::string>>::iterator iter;
        while (getline(inFile, strLine))
        {
            if (ExtractConfig(strLine, strSection, strKey, strValue))
            {
                iter = m_settings.find(strSection);
                if (iter != m_settings.end())
                {
                    mapKeyValue[strKey] = strValue;
                    iter->second = mapKeyValue;
                }
                else
                {
                    mapKeyValue.clear();
                    m_settings.insert(std::make_pair(strSection, mapKeyValue));
                }
            }
            strKey.clear();
            strValue.clear();
        }
        inFile.close();
        return true;
    }

    std::string Config::GetString(const char *szSection, const char *szKey, const char *szDefaultValue)
    {
        std::string strSection(szSection);
        std::string strKey(szKey);
        std::string strDefaultValue(szDefaultValue);
        std::map<std::string, std::string> mapKeyValue;
        std::map<std::string, std::string>::iterator mapIter;
        std::map<std::string, std::map<std::string, std::string>>::iterator iter;

        // 寻找section
        iter = m_settings.find(strSection);
        if (iter == m_settings.end())
        {
            return strDefaultValue;
        }
        mapKeyValue = iter->second;

        // 寻找key
        mapIter = mapKeyValue.find(strKey);
        if (mapIter == mapKeyValue.end())
        {
            return strDefaultValue;
        }

        return mapIter->second;
    }

    int Config::GetInt(const char *szSection, const char *szKey, const int &szDefaultValue)
    {
        std::string strSection(szSection);
        std::string strKey(szKey);
        std::map<std::string, std::string> mapKeyValue;
        std::map<std::string, std::string>::iterator mapIter;
        std::map<std::string, std::map<std::string, std::string>>::iterator iter;

        // 寻找section
        iter = m_settings.find(strSection);
        if (iter == m_settings.end())
        {
            return szDefaultValue;
        }
        mapKeyValue = iter->second;

        // 寻找key
        mapIter = mapKeyValue.find(strKey);
        if (mapIter == mapKeyValue.end())
        {
            return szDefaultValue;
        }
        return atoi(mapIter->second.c_str());
    }

    double Config::GetDouble(const char *szSection, const char *szKey, const double &szDefaultValue)
    {
        std::string strSection(szSection);
        std::string strKey(szKey);
        std::map<std::string, std::string> strKeyValue;
        std::map<std::string, std::string>::iterator mapIter;
        std::map<std::string, std::map<std::string, std::string>>::iterator iter;

        // 寻找section
        iter = m_settings.find(strSection);
        if (iter == m_settings.end())
        {
            return szDefaultValue;
        }
        strKeyValue = iter->second;

        // 寻找key
        mapIter = strKeyValue.find(strKey);
        if (mapIter == strKeyValue.end())
        {
            return szDefaultValue;
        }
        return atof(mapIter->second.c_str());
    }
} // namespace ini
