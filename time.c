
#include "time.h"
#include <platform_config.h>
#ifdef CONTIKI
#include <contiki/core/sys/etimer.h>
#endif

extern uint32_t SystemCoreClock;

void sleep_ms(uint32_t ms) {
  volatile uint32_t i;
  for (i = ms; i != 0; i--) {
    sleep_us(1000);
  }
}

void sleep_us(uint32_t us) {
  volatile uint32_t i;
  for (i = ((SystemCoreClock / 8000000) * us); i != 0; i--) {}
}

#ifdef CONTIKI
void HAL_SYSTICK_Callback() {
  etimer_request_poll();
}

CCIF unsigned long clock_seconds() {
  return HAL_GetTick() / 1000;
}

clock_time_t clock_time(void) {
  return HAL_GetTick();
}
#endif
