#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace Mistiq {
	class ExcelReader {
	public:
		std::map<std::string, std::string> GetCSV(std::string a_FilePath);
	};
}