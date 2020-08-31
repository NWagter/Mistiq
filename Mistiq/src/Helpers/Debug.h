#pragma once

namespace Mistiq
{
    enum LogType
    {
        None,
        Engine,
        Game
    };
	struct LogMessage
	{
		LogType type;
		std::string message;
		std::string time;

        LogMessage(LogType a_Type, std::string a_Message, std::string a_Time)
        {
			type = a_Type;
			message = a_Message;
			time = a_Time;
        }
	};
	class Debug
	{
	public:
        Debug() {}
        ~Debug() {}

		void Log(LogType a_LogType, std::string a_Type);

		void ClearConsoleLogs() { m_ConsoleLogs.clear(); }
		std::vector<LogMessage>& GetConsoleLogs() { return m_ConsoleLogs; }

	private:
		std::vector<LogMessage> m_ConsoleLogs;
	};
}


