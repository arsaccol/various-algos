#include "timer.h"
#include <iostream>

void Timer::start()
{
    begin = std::chrono::steady_clock::now();
}

std::chrono::nanoseconds Timer::getNanosecondsElapsed()
{
    auto end = std::chrono::steady_clock::now();

    return std::chrono::nanoseconds{end - begin};
}

