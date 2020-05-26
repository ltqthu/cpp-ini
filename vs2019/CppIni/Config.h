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

        // ��ȡ�����ļ�
        bool ReadConfig(const std::string& filename);

        // ��ȡ�ַ���
        std::string GetString(const char* szSection, const char* szKey, const char* szDefaultValue);

        // ��ȡ����
        int GetInt(const char* szSection, const char* szKey, const int& szDefaultValue);

        // ��ȡ������
        double GetDouble(const char* szSection, const char* szKey, const double& szDefaultValue);

    private:
        // �ж��Ƿ���space����tab
        bool IsSpaceTab(char c);
        // �ж��Ƿ��Ǳ�ע��ʶ��#
        bool IsComment(char c);
        // ɾ����β�Ŀո�
        void Trim(std::string& str);
        // ��һ������ȡ������Ϣ
        bool ExtractConfig(const std::string& strLine, std::string& strSection, std::string& strKey, std::string& strValue);

    private:
        std::map<std::string, std::map<std::string, std::string> >m_settings;
    };
}
#endif
