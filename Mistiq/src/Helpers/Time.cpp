#include "Mstqpch.h"
#include "Time.h"

std::string Mistiq::Time::GetCurrentTime()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[9];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
	std::string str(buffer);
	return str;
}
