#ifndef TIMER_H
#define TIMER_H
#include<SDL2/SDL.h>
#include <stdio.h>

class Timer
{
    public:
        Timer(float = 1);
        int getTime();
        void setTimerFrequence(float);
        void startTimer();
        void pauseTimer();
        void resumeTimer();

    private:
        Uint32 startTime, pauseTime;
        float frequence;
        bool pause;

};

#endif // TIMER_H
