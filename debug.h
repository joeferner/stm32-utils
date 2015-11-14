
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <platform_config.h>

#ifdef HAL_UART_MODULE_ENABLED

void debug_setup();

#ifndef CONTIKI
void debug_tick();
#endif

#endif

#endif
