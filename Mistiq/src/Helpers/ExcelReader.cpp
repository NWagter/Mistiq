#include "Mstqpch.h"
#include "ExcelReader.h"
#include <filesystem>

std::map<std::string, std::string> Mistiq::ExcelReader::GetCSV(std::string a_FilePath) {
	std::map<std::string, std::string> m_Values;

	std::cout << std::filesystem::current_path() << std::endl;

	std::ifstream infile(a_FilePath);
	std::string line;
	while (std::getline(infile, line)) {
		std::string w1, w2;
		bool fillingw1 = true;
		for (int i = 0; i < line.length(); i++) {
			char c = line[i];

			if (c != ',') {
				if (fillingw1) {
					w1 += c;
				}
				else {
					w2 += c;
				}

			}
			else {
				fillingw1 = false;
			}
		}
		m_Values.emplace(std::make_pair(w1, w2));
	}
	return m_Values;
}
