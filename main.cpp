#include <iostream>
#include <map>
#include <string>

// ���ع���ǰ׺����
const std::map<std::string, std::string> & loadCountryPrefixRules() {
    static std::map<std::string, std::string> countryPrefixRules;
    countryPrefixRules["B"] = "�й�";
    return countryPrefixRules;
}

// ���ص�̨�������
const std::map<char, std::string> & loadStationTypeRules() {
    static std::map<char, std::string> stationTypeRules;
    stationTypeRules['A'] = "����ҵ���̨��һ����";
    stationTypeRules['D'] = "����ҵ���̨��������";
    stationTypeRules['E'] = "����ҵ���̨��������";
    stationTypeRules['G'] = "����ҵ���̨���������ļ����弶������̨����";
    stationTypeRules['H'] = "����ҵ���̨���������ļ����弶������̨����";
    stationTypeRules['I'] = "����ҵ���̨���������ļ����弶������̨����";
    stationTypeRules['J'] = "ҵ���ű�̨";
    stationTypeRules['L'] = "�⼮����ۡ����š�̨�������Ա���й��ڵ����õ�ҵ���̨";
    stationTypeRules['R'] = "ҵ���м�̨";
    stationTypeRules['T'] = "����ҵ���̨";
    stationTypeRules['Y'] = "����ҵ���̨";
    return stationTypeRules;
}

// ���ش�����ʡ�ݷ�Χ����
const std::map<char, std::map<std::string, std::pair<std::string, std::string> > > & loadRegionProvinceRules() {
    static std::map<char, std::map<std::string, std::pair<std::string, std::string> > > regionProvinceRules;

    // ��1��������
    regionProvinceRules['1'] = {
        {"����", {"AA", "XZZ"}}
    };

    // ��2����������������������
    regionProvinceRules['2'] = {
        {"������", {"AA", "HZZ"}},
        {"����", {"IA", "PZZ"}},
        {"����", {"QA", "XZZ"}}
    };

    // ��3�����ӱ������ɹš�ɽ�������
    regionProvinceRules['3'] = {
        {"���", {"AA", "FZZ"}},
        {"���ɹ�", {"GA", "LZZ"}},
        {"�ӱ�", {"MA", "RZZ"}},
        {"ɽ��", {"SA", "XZZ"}}
    };

    // ��4����ɽ�������ա��Ϻ�
    regionProvinceRules['4'] = {
        {"�Ϻ�", {"AA", "HZZ"}},
        {"ɽ��", {"IA", "PZZ"}},
        {"����", {"QA", "XZZ"}}
    };

    // ��5�����㽭������������
    regionProvinceRules['5'] = {
        {"�㽭", {"AA", "HZZ"}},
        {"����", {"IA", "PZZ"}},
        {"����", {"QA", "XZZ"}}
    };

    // ��6�������ϡ�����������
    regionProvinceRules['6'] = {
        {"����", {"AA", "HZZ"}},
        {"����", {"IA", "PZZ"}},
        {"����", {"QA", "XZZ"}}
    };

    // ��7�������ϡ��㶫������������
    regionProvinceRules['7'] = {
        {"����", {"AA", "HZZ"}},
        {"�㶫", {"IA", "PZZ"}},
        {"����", {"QA", "XZZ"}},
        {"����", {"YA", "ZZZ"}}
    };

    // ��8�����Ĵ������ݡ����ϡ�����
    regionProvinceRules['8'] = {
        {"�Ĵ�", {"AA", "FZZ"}},
        {"����", {"GA", "LZZ"}},
        {"����", {"MA", "RZZ"}},
        {"����", {"SA", "XZZ"}}
    };

    // ��9�������������ࡢ���ġ��ຣ
    regionProvinceRules['9'] = {
        {"����", {"AA", "FZZ"}},
        {"����", {"GA", "LZZ"}},
        {"����", {"MA", "RZZ"}},
        {"�ຣ", {"SA", "XZZ"}}
    };

    // ��0�����½�������
    regionProvinceRules['0'] = {
        {"�½�", {"AA", "FZZ"}},
        {"����", {"GA", "LZZ"}}
    };

    return regionProvinceRules;
}

// �жϺ�׺�Ƿ��ڷ�Χ��
bool isWithinRange(const std::string &suffix, const std::string &rangeStart, const std::string &rangeEnd) {
    return suffix >= rangeStart && suffix <= rangeEnd;
}

// �ַ���ת��д
const std::string toUpper(const std::string &callSign){
    std::string upperCallSign = callSign;
    for (auto s = upperCallSign.begin(); s != upperCallSign.end(); s++)
        *s = toupper(*s);
    return upperCallSign;
}

// ��ѯ����
void queryCallSign(const std::string &callSign) {
    // ���ظ������
    auto countryRules = loadCountryPrefixRules();
    auto stationTypeRules = loadStationTypeRules();
    auto regionProvinceRules = loadRegionProvinceRules();

    // ȷ������������5λ
    if (callSign.length() < 5) {
        std::cout << "���Ÿ�ʽ����ȷ" << std::endl;
        return;
    }

    // ��������ǰ׺
    std::string country = countryRules[callSign.substr(0, 1)];

    // ������̨����
    char stationType = callSign[1];
    std::string station = stationTypeRules[stationType];

    // ������������
    char region = callSign[2];

    // ������׺
    std::string suffix = callSign.substr(3, 2); // �����׺����Ϊ2λ

    // ���Ҹõ�����ʡ�ݷ�Χ
    std::string provinceName = "δ֪ʡ��";
    if (regionProvinceRules.find(region) != regionProvinceRules.end()) {
        for (const auto &province: regionProvinceRules[region]) {
            if (isWithinRange(suffix, province.second.first, province.second.second)) {
                provinceName = province.first;
                break;
            }
        }
    }
    // �������������ҵ���ű�̨������ҵ���̨������ҵ���̨��
    if (stationType == 'J') {
        char suffix1 = callSign[3];
        if (suffix1 == 'H' || suffix1 == 'V' || suffix1 == 'U') {
            station = "HF��VHF��UHVƵ���ű�̨";
        } else if (suffix1 == 'D') {
            station = "ҵ�����ߵ����ר���ű�̨";
        } else if (suffix1 == 'S' && region == '1') {
            station = "����ҵ���̨";
        } else if (suffix1 == 'T') {
            station = "����ҵ���̨";
        }
    }
    // ������
    if (!country.empty() && !station.empty() && provinceName != "δ֪ʡ��") {
        std::cout << "����: " << callSign << std::endl;
        std::cout << "����: " << country << std::endl;
        std::cout << "��̨����: " << station << std::endl;
        std::cout << "ʡ��: " << provinceName << std::endl;
    } else {
        std::cout << "δ�ҵ����Ŷ�Ӧ����Ϣ" << std::endl;
    }
}

int main() {
    std::string callSign;
    std::cout << "������Ҫ��ѯ�ĺ���: ";
    std::cin >> callSign;
    std::cout << "\n��ѯ�������:\n\n";

    // ��ѯ������Ϣ
    std::string upperCallSign = toUpper(callSign);  // ����ת��д
    queryCallSign(upperCallSign);
    std::cin.get();
    std::cout << "\n���س����˳���";
    std::cin.get();
    return 0;
}

