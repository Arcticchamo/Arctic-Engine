#ifndef TIME_H
#define TIME_H

#include <chrono>

using namespace std::chrono;

class Time
{
private:
	static time_point<std::chrono::system_clock> m_lastTick; 

public:

	static void Start();
	static double deltaTime();
};



#endif