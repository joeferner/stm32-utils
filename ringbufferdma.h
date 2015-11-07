
#ifndef _RINGBUFFER_DMA_H_
#define _RINGBUFFER_DMA_H_

#include <platform_config.h>
#include <stdbool.h>

typedef struct {
  uint8_t* buffer;
  uint16_t size;
  uint8_t* tailPtr;
  DMA_HandleTypeDef* dmaHandle;
} RingBufferDmaU8;

void RingBufferDmaU8_initUSARTRx(RingBufferDmaU8* ring, UART_HandleTypeDef* husart, uint8_t* buffer, uint16_t size);
uint16_t RingBufferDmaU8_available(RingBufferDmaU8* ring);
bool RingBufferDmaU8_readLine(RingBufferDmaU8* ring, char* line, uint16_t size);
uint8_t RingBufferDmaU8_read(RingBufferDmaU8* ring);

#endif

