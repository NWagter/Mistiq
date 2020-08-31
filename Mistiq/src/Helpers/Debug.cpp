#include "Mstqpch.h"
#include "Debug.h"
#include "Time.h"

void Mistiq::Debug::Log(LogType a_LogType, std::string a_Type)
{
	std::string time = "[";
	time.append(Time::GetCurrentTime());
	time.append("]");

    switch (a_LogType)
    {
	case None:
		break;
	case Engine:
		break;
	case Game:
        
		const LogMessage log(Game, a_Type, time);
		m_ConsoleLogs.push_back(log);
		break;
    }
}
