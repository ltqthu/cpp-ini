#include "Config.h"
#include <fstream>
//#include <stdlib.h>

namespace ini
{
    Config::Config(){}
    Config::~Config(){}

    bool Config::IsSpaceTab(char c)
    {
        if (' ' == c || '\t' == c)
        {
            return true;
        }
        return false;
    }

    bool Config::IsCommentChar(char c)
    {
        switch (c)
        {
        case '#':
            return true;
        default:
            return false;
        }
    }

    void Config::TrimSpaceTab(std::string& str)
    {
        if (str.empty())
        {
            return;
        }

        int i, nStartPos, nEndPos;
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
        nStartPos = i;

        for (i = str.size() - 1; i >= 0; --i)
        {
            if (!IsSpaceTab(str[i])) 
            {
                break;
            }
        }
        nEndPos = i;

        str = str.substr(nStartPos, nEndPos - nStartPos + 1);
    }

    //void Config::ReplaceSpaceTab(std::string& str)
    //{
    //    str = str.replace(str.begin(), str.end(), )

    //}

    bool Config::AnalyseLine(const std::string& strLine, std::string& strSection, std::string& strKey, std::string& strValue)
    {
        if (strLine.empty())
        {
            return false;
        }

        int nStartPos = 0, nEndPos = strLine.size() - 1, nPos, nStartPosOfBracket, nEndPosOfBracket;

        if ((nPos = strLine.find("#")) != std::string::npos)
        {
            if (0 == nPos)
            {
                return false;
            }
            nEndPos = nPos - 1;
        }

        if (((nStartPosOfBracket = strLine.find("[")) != std::string::npos) && ((nEndPosOfBracket = strLine.find("]"))) != std::string::npos)
        {
            strSection = strLine.substr(nStartPosOfBracket + 1, nEndPosOfBracket - 1);
            return true;
        }

        std::string strNewLine = strLine.substr(nStartPos, nStartPos + 1 - nEndPos);
        if ((nPos = strNewLine.find('=')) == -1)
        {
            return false;
        }

        strKey = strNewLine.substr(0, nPos);
        strValue = strNewLine.substr(nPos + 1, nEndPos + 1 - (nPos + 1));
        TrimSpaceTab(strKey);
        if (strKey.empty()) 
        {
            return false;
        }

        TrimSpaceTab(strValue);
        if ((nPos = strValue.find("\r")) > 0)
        {
            strValue.replace(nPos, 1, "");
        }

        if ((nPos = strValue.find("\n")) > 0)
        {
            strValue.replace(nPos, 1, "");
        }

        return true;
    }

    bool Config::ReadConfig(const std::string& strFilename)
    {
        m_settings.clear();
        std::ifstream inFile(strFilename.c_str());
        if (!inFile)
        {
            return false;
        }
        std::string strLine, strKey, strValue, strSection;
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::map<std::string, std::string> >::iterator iter;
        while (getline(inFile, strLine))
        {
            if (AnalyseLine(strLine, strSection, strKey, strValue))
            {
                iter = m_settings.find(strSection);

                if (iter != m_settings.end()) // 找到
                {
                    k_v[strKey] = strValue;
                    iter->second = k_v;
                }
                else // 没找到
                {
                    k_v.clear();
                    m_settings.insert(std::make_pair(strSection, k_v));
                }
            }
            strKey.clear();
            strValue.clear();
        }
        inFile.close();
        return true;
    }

    std::string Config::ReadString(const char* section, const char* item, const char* default_value)
    {
        std::string strSection(section);
        std::string strItem(item);
        std::string strDefault(default_value);
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::string>::iterator it_item;
        std::map<std::string, std::map<std::string, std::string> >::iterator iter;
        iter = m_settings.find(strSection);
        if (iter == m_settings.end())
        {
            return strDefault;
        }
        k_v = iter->second;
        it_item = k_v.find(strItem);
        if (it_item == k_v.end())
        {
            std::cout << "ltq" << std::endl;
            return it_item->second;

//            return strDefault;
        }
        return it_item->second;
    }

    int Config::ReadInt(const char* section, const char* item, const int& default_value)
    {
        std::string strSection(section);
        std::string strItem(item);
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::string>::iterator it_item;
        std::map<std::string, std::map<std::string, std::string> >::iterator it;
        it = m_settings.find(strSection);
        if (it == m_settings.end())
        {
            return default_value;
        }
        k_v = it->second;
        it_item = k_v.find(strItem);
        if (it_item == k_v.end())
        {
            return default_value;
        }
        return atoi(it_item->second.c_str());
    }

    float Config::ReadFloat(const char* section, const char* item, const float& default_value)
    {
        std::string strSection(section);
        std::string strItem(item);
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::string>::iterator it_item;
        std::map<std::string, std::map<std::string, std::string> >::iterator it;
        it = m_settings.find(strSection);
        if (it == m_settings.end())
        {
            return default_value;
        }
        k_v = it->second;
        it_item = k_v.find(strItem);
        if (it_item == k_v.end())
        {
            return default_value;
        }
        return atof(it_item->second.c_str());
    }
}

