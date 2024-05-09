#include <time.h>
#include <sys/time.h>

#include "../inc/my_time.h"
/**
 * @brief Returns the current time in microseconds.
 *
 * @return Current time in microseconds, or (unsigned long long) -1 on error.
 */
microsecond_t microseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;

    return val.tv_sec * 1000000ULL + val.tv_usec;
}
