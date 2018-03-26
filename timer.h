#ifndef TIMER_H
#define TIMER_H
#include <chrono>

struct Timer
{
    void start();
    std::chrono::nanoseconds getNanosecondsElapsed();
    std::chrono::milliseconds getMillisecondsElapsed();

private:

    std::chrono::time_point<std::chrono::steady_clock> begin;
};

#endif
