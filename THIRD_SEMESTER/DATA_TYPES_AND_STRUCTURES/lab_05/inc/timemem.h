#ifndef TIMEMEM_H
#define TIMEMEM_H

#include "app.h"
#include "array.h"
#include "list.h"
/**
 * @brief Generates a random time within the given time range.
 *
 * @param t The time range.
 * @return double The randomly generated time.
 */
double getime(times_r t);
/**
 * @brief Returns the current timestamp using the RDTSC instruction.
 *
 * @return int64_t The current timestamp.
 */
int64_t tick(void);
/**
 * @brief Simulates memory input/output operations.
 */
void memory_io();

#endif
