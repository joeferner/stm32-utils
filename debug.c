
#include "debug.h"

#ifdef HAL_UART_MODULE_ENABLED

#include <utils/utils.h>
#include <stdio.h>
#include <string.h>
#include <utils/ringbufferdma.h>
#ifdef CONTIKI
#include <contiki/core/sys/process.h>

PROCESS(debug_process, "Debug");
#endif

#define DEBUG_RX_BUFFER_SIZE 32
RingBufferDmaU8 debugRxRing;
uint8_t debugRxBuffer[DEBUG_RX_BUFFER_SIZE];

__weak void debug_processLine(const char* line);

void debug_setup() {
  RingBufferDmaU8_initUSARTRx(&debugRxRing, &DEBUG_UART, debugRxBuffer, DEBUG_RX_BUFFER_SIZE);
#ifdef CONTIKI
  process_start(&debug_process, NULL);
#endif
}

__weak void debug_processLine(const char* line) {
  if (strlen(line) == 0) {
  } else {
    printf("invalid debug command: %s\n", line);
  }
  printf("> ");
}

#ifdef CONTIKI
PROCESS_THREAD(debug_process, ev, data) {
  char line[30];

  PROCESS_BEGIN();
  while (1) {
    PROCESS_PAUSE();
    if (RingBufferDmaU8_readLine(&debugRxRing, line, sizeof(line)) > 0) {
      strTrimRight(line);
      debug_processLine(line);
    }
  }
  PROCESS_END();
}
#else
void debug_tick() {
  char line[30];
  if (RingBufferDmaU8_readLine(&debugRxRing, line, sizeof(line)) > 0) {
    strTrimRight(line);
    debug_processLine(line);
  }
}
#endif

#ifdef __GNUC__
#  define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#  define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#  define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#  define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE {
  HAL_UART_Transmit(&DEBUG_UART, (uint8_t*)&ch, 1, MAX_TIMEOUT);
  return ch;
}

GETCHAR_PROTOTYPE {
  while (RingBufferDmaU8_available(&debugRxRing) == 0);
  return RingBufferDmaU8_read(&debugRxRing);
}

#endif
