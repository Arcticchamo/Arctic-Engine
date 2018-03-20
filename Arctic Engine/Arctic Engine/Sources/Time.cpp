#include "..\headers\Time.h"

time_point<std::chrono::system_clock> Time::m_lastTick; 

void Time::Start()
{
	m_lastTick = system_clock::now();
}

double Time::deltaTime()
{
	return 1/60.0f;
}