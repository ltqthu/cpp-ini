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

    void Config::Trim(std::string& str)
    {
        // �ж��Ƿ�Ϊ��
        if (str.empty())
        {
            return;
        }

        // �������жϣ�������ǿո��򷵻ؿ��ַ���
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
        nStartPos = i; // �����ң���һ���ǿ��ַ���λ��

        // ���ҵ����жϣ�������ǿո��򷵻ؿ��ַ���
        for (i = str.size() - 1; i >= 0; --i) 
        {
            if (!IsSpaceTab(str[i])) 
            {
                break;
            }
        }
        nEndPos = i; // ���ҵ��󣬵�һ���ǿ��ַ�����λ��

        str = str.substr(nStartPos, nEndPos - nStartPos + 1);
    }

    bool Config::ExtractConfig(const std::string& strLine, std::string& strSection, std::string& strKey, std::string& strValue)
    {
        // ��ȫ���
        if (strLine.empty())
        {
            return false;
        }

        size_t nPos;                         // �ƶ���λ��
        size_t nStartPos = 0;                // ��ʼλ��
        size_t nEndPos = strLine.size() - 1; // ����λ��
        size_t nStartPosOfBracket;           // ���ſ�ʼ��λ��
        size_t nEndPosOfBracket;             // ���Ž�����λ��

        // ���а���#
        if ((nPos = strLine.find("#")) != std::string::npos)
        {
            // ��һ���ַ���#�������ж���ע��
            if (0 == nPos)
            {
                return false;
            }
            // #�������ַ�
            nEndPos = nPos - 1;
        }

        // ��ȡ��section
        if (((nStartPosOfBracket = strLine.find("[")) != std::string::npos) && ((nEndPosOfBracket = strLine.find("]"))) != std::string::npos)
        {
            strSection = strLine.substr(nStartPosOfBracket + 1, nEndPosOfBracket - 1);
            return true;
        }

        // ��ȡ��ȥ��#ע�͵�key=value
        std::string strNewLine = strLine.substr(nStartPos, nStartPos + 1 - nEndPos);
        // û�ҵ��Ⱥ�
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


    bool Config::ReadConfig(const std::string& strFilename)
    {
        // �������
        m_settings.clear();

        // ��ȡ�ļ�
        std::ifstream inFile(strFilename.c_str());
        if (!inFile)
        {
            return false;
        }

        std::string strLine, strSection, strKey, strValue;
        std::map<std::string, std::string> mapKeyValue;
        std::map<std::string, std::map<std::string, std::string> >::iterator iter;
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

    std::string Config::GetString(const char* szSection, const char* szKey, const char* szDefaultValue)
    {
        std::string strSection(szSection);
        std::string strKey(szKey);
        std::string strDefaultValue(szDefaultValue);
        std::map<std::string, std::string> mapKeyValue;
        std::map<std::string, std::string>::iterator mapIter;
        std::map<std::string, std::map<std::string, std::string> >::iterator iter;

        // Ѱ��section
        iter = m_settings.find(strSection);
        if (iter == m_settings.end())
        {
            return strDefaultValue;
        }
        mapKeyValue = iter->second;

        // Ѱ��key
        mapIter = mapKeyValue.find(strKey);
        if (mapIter == mapKeyValue.end())
        {
            return strDefaultValue;
        }

        return mapIter->second;
    }

    int Config::GetInt(const char* szSection, const char* szKey, const int& szDefaultValue)
    {
        std::string strSection(szSection);
        std::string strKey(szKey);
        std::map<std::string, std::string> mapKeyValue;
        std::map<std::string, std::string>::iterator mapIter;
        std::map<std::string, std::map<std::string, std::string> >::iterator iter;

        // Ѱ��section
        iter = m_settings.find(strSection);
        if (iter == m_settings.end())
        {
            return szDefaultValue;
        }
        mapKeyValue = iter->second;

        // Ѱ��key
        mapIter = mapKeyValue.find(strKey);
        if (mapIter == mapKeyValue.end())
        {
            return szDefaultValue;
        }
        return atoi(mapIter->second.c_str());
    }

    double Config::GetDouble(const char* szSection, const char* szKey, const double& szDefaultValue)
    {
        std::string strSection(szSection);
        std::string strKey(szKey);
        std::map<std::string, std::string> strKeyValue;
        std::map<std::string, std::string>::iterator mapIter;
        std::map<std::string, std::map<std::string, std::string> >::iterator iter;

        // Ѱ��section
        iter = m_settings.find(strSection);
        if (iter == m_settings.end())
        {
            return szDefaultValue;
        }
        strKeyValue = iter->second;

        // Ѱ��key
        mapIter = strKeyValue.find(strKey);
        if (mapIter == strKeyValue.end())
        {
            return szDefaultValue;
        }
        return atof(mapIter->second.c_str());
    }
}
