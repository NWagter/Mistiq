#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "../Helpers/ExcelReader.h"

namespace Mistiq {
	class Localization {
	public:
		void LoadLanguageData();

        std::string GetValueFromKey(std::string a_Key);
		void SetLanguage(std::string a_LanguageName);

	private:
		std::map<std::string, int> m_Languages;
		unsigned int m_CurrentLanguage = 0;

		std::vector<std::map<std::string, std::string>> m_LanguageData;
	};
}


