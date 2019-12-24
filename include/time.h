#ifndef _STM32LIB_TIME_H
#define _STM32LIB_TIME_H

#include <stdint.h>
#include <sys/_timeval.h>

#ifdef  __cplusplus
extern "C" {
#endif

void sleep_ms(uint32_t ms);
void sleep_us(uint32_t us);

struct tm* gmtime(register const time_t* timer);

#ifdef  __cplusplus
}
#endif

#endif  /* _STM32LIB_TIME_H */

