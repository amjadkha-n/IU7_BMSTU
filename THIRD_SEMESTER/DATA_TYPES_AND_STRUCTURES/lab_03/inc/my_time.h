#ifndef MY_TIME_H
#define MY_TIME_H

typedef unsigned long long microsecond_t;
#define MSC "llu" // Спецификатор для типа microsecond_t
/**
 * @brief Returns the current time in microseconds.
 *
 * @return Current time in microseconds, or (unsigned long long) -1 on error.
 */
microsecond_t microseconds_now(void);

#endif