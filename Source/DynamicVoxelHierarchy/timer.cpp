#include "timer.h"

timer::timer()
{
    seconds = time(NULL);
}

void timer::setTime()
{
    seconds = time(NULL);
}

time_t timer::timeElapsed()
{
    return time(NULL) - seconds;
}
