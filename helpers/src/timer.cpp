#include "../include/timer.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <raylib.h>

Timer::Timer(int milliseconds)
    : duration(milliseconds) {}

Timer&
Timer::start()
{
    if (!hasStarted)
    {
        startTime  = std::chrono::steady_clock::now();
        hasStarted = true;
        progress   = 0.0f;

        if (onStart)
            onStart();
    }

    return *this;
}

Timer&
Timer::reset()
{
    hasStarted = false;
    progress   = 0.0f;

    if (onReset)
        onReset();

    return *this;
}

Timer&
Timer::update()
{
    if (hasElapsed() || !hasStarted)
        return *this;

    const auto currentTime = std::chrono::steady_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                                 currentTime - startTime)
                                 .count();

    progress = std::min(1.0f, (float)elapsedTime / duration);

    if (onTick)
        onTick(progress);

    if (progress == 1.0f && onFinish)
        onFinish();

    return *this;
}

bool
Timer::hasElapsed() const
{
    return progress == 1.0f;
}