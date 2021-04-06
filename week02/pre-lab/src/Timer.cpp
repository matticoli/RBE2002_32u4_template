#include "Timer.h"
#include <Arduino.h>

/**
 * Create a timer that will expire every "interval"
 **/
Timer::Timer(unsigned long interval)
{
    reset();
    timeInterval = interval;
}

/**
 * Reset the timer so that the expired time is the current time + interval
 */
void Timer::reset()
{
    expiredTime = millis();
}

/**
 * Change the timer interval to "NewInterval" then
 * reset the timer to that the expired time is the current time + interval
 */
void Timer::reset(unsigned long newInterval)
{
    timeInterval = newInterval;
    reset();
}

/**
 * Check if the timer is expired, that is the current time is past
 * the expired time.
 */
bool Timer::isExpired()
{
    // Check if millis has rolled over
    if (millis() < expiredTime) {
        expiredTime = timeInterval - (__LONG_MAX__ - expiredTime);
    }
    if (millis() - expiredTime > timeInterval)
    {
        reset();
        return true;
    }
    return false;
}
