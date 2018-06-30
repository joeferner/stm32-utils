
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <platform.h>

#define DEBUG_TIMEOUT 1000

#if defined(CONFIG_DEBUG_UART1)
extern UART_HandleTypeDef huart1;
#define DEBUG_UART huart1
#elif defined(CONFIG_DEBUG_UART2)
extern UART_HandleTypeDef huart2;
#define DEBUG_UART huart2
#elif defined(CONFIG_DEBUG_UART3)
extern UART_HandleTypeDef huart3;
#define DEBUG_UART huart3
#elif defined(CONFIG_DEBUG_UART4)
extern UART_HandleTypeDef huart4;
#define DEBUG_UART huart4
#elif defined(CONFIG_DEBUG_UART5)
extern UART_HandleTypeDef huart5;
#define DEBUG_UART huart5
#else
#error "CONFIG_DEBUG_UARTx not defined"
#endif

void debug_setup();

#ifndef CONTIKI
void debug_tick();
#endif

#endif
