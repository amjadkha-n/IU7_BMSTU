/**
 * @file timer.h
 * @brief Timer function for measuring CPU ticks.
 */
#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
/**
 * @brief Returns the current value of the CPU tick counter.
 *
 * @return Current value of the CPU tick counter.
 */
uint64_t tick(void);

#endif
