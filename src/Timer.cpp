#include "../include/Timer.h"




Timer::Timer(float xfrequence)
    :startTime(0), frequence(xfrequence)
{
    startTimer();
}

void Timer::startTimer()
{
    pause = false;
    startTime = SDL_GetTicks();
}

void Timer::pauseTimer()
{
pause = true;
pauseTime = SDL_GetTicks() - startTime;
startTime = 0;

}

void Timer::resumeTimer()
{
pause = false;

startTime = SDL_GetTicks()  - pauseTime;
pauseTime = 0;
}

void Timer::setTimerFrequence(float xfrequence)
{
    frequence = xfrequence;
}


int Timer::getTime( )
{
    if (!pause)
    {
        long double cTime = SDL_GetTicks();

        if ( ( (cTime - startTime) /1000 ) >= frequence)
        {
            startTime = SDL_GetTicks();
            return 1;
        }

        else return 0;
    }

return 0;
}
