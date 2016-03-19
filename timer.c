
#include "timer.h"
#include <platform_config.h>

void periodicTimer_setup(PeriodicTimer* timer, uint32_t intervalMs) {
  timer->nextTick = HAL_GetTick() + intervalMs;
  timer->intervalMs = intervalMs;
}

bool periodicTimer_hasElapsed(PeriodicTimer* timer) {
  int32_t currentTime = HAL_GetTick();
  if (currentTime > timer->nextTick) {
    timer->nextTick = currentTime + timer->intervalMs;
    return true;
  } else {
    return false;
  }
}
