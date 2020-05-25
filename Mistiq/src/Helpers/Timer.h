#pragma once
#include <chrono>

namespace Mistiq
{
	enum class ETimerType
	{
		SECONDS,
		MILLIS,
		MICROS
	};

	class Timer
	{
	public:
	    Timer();

		std::float_t GetTimeAs() const;

		void Reset();

	private:
		std::chrono::high_resolution_clock::time_point begin;
	};
}
