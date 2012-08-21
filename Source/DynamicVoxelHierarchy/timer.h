#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class timer
{
    time_t seconds;

public:
    timer();

    void setTime();
    time_t timeElapsed();
};

#endif // TIMER_H
