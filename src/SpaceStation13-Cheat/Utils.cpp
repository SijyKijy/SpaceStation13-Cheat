#include <chrono>
#include <iomanip>
#include <iostream>

#include "Config.h"

static void Log(std::string text)
{
#ifdef DEBUG_CONSOLE
	auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S") << " " + text << std::endl;
#endif
}