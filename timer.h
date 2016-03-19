
#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint32_t nextTick;
  uint32_t intervalMs;
} PeriodicTimer;

void periodicTimer_setup(PeriodicTimer* timer, uint32_t intervalMs);
bool periodicTimer_hasElapsed(PeriodicTimer* timer);

#endif
