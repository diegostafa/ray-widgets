#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <functional>

class Timer
{
private:
    std::chrono::steady_clock::time_point startTime;

public:
    int   duration   = 0;
    float progress   = 0.0f;
    bool  hasStarted = false;

    std::function<void()>      onStart  = nullptr;
    std::function<void(float)> onTick   = nullptr;
    std::function<void()>      onFinish = nullptr;
    std::function<void()>      onReset  = nullptr;

    Timer(int milliseconds = 0);
    Timer& start();
    Timer& reset();
    Timer& update();
    bool   hasElapsed() const;
};

#endif