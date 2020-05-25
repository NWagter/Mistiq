#include "Mstqpch.h"
#include "Timer.h"

Mistiq::Timer::Timer()
{
	Reset();
}

std::float_t Mistiq::Timer::GetTimeAs() const
{
	const auto current = std::chrono::high_resolution_clock::now();
	const auto difference = static_cast<std::float_t>(std::chrono::duration_cast<std::chrono::microseconds>(current - begin).count());

	std::float_t time = 0;

	time = difference / 1000000.f;

	return time;
}

void Mistiq::Timer::Reset()
{
	begin = std::chrono::high_resolution_clock::now();
}
