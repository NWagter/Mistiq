#include "Mstqpch.h"
#include "Localization.h"

void Mistiq::Localization::LoadLanguageData() {
	ExcelReader reader;

    m_LanguageData.push_back(reader.GetCSV("EnglishData.csv"));
	m_Languages.insert(std::pair<std::string, int>("English", 0));

	m_LanguageData.push_back(reader.GetCSV("DutchData.csv"));
	m_Languages.insert(std::pair<std::string, int>("Dutch", 1));

	m_LanguageData.push_back(reader.GetCSV("FrenchData.csv"));
	m_Languages.insert(std::pair<std::string, int>("French", 2));

	SetLanguage("Dutch");
}

std::string Mistiq::Localization::GetValueFromKey(std::string a_Key) {
	return m_LanguageData[m_CurrentLanguage].find(a_Key)->second;
}

void Mistiq::Localization::SetLanguage(std::string a_LanguageName) {
	int language = m_Languages.find(a_LanguageName)->second;
	m_CurrentLanguage = language;
}
