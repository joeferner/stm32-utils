
#include "ringbufferdma.h"

#ifdef HAL_DMA_MODULE_ENABLED

#include "utils.h"

void RingBufferDmaU8_initUSARTRx(RingBufferDmaU8* ring, UART_HandleTypeDef* husart, uint8_t* buffer, uint16_t size) {
  ring->buffer = buffer;
  ring->size = size;
  ring->tailPtr = buffer;
  ring->dmaHandle = husart->hdmarx;
  HAL_UART_Receive_DMA(husart, buffer, size);
}

uint16_t RingBufferDmaU8_available(RingBufferDmaU8* ring) {
#ifdef __HAL_DMA_GET_COUNTER
  uint32_t leftToTransfer = __HAL_DMA_GET_COUNTER(ring->dmaHandle);
#else
  uint32_t leftToTransfer = ring->dmaHandle->Instance->CNDTR;
#endif
  volatile uint8_t const* head = ring->buffer + ring->size - leftToTransfer;
  volatile uint8_t const* tail = ring->tailPtr;
  if (head >= tail) {
    return head - tail;
  } else {
    return head - tail + ring->size;
  }
}

bool RingBufferDmaU8_readLine(RingBufferDmaU8* ring, char* line, uint16_t size) {
  volatile uint8_t* in = ring->tailPtr;
  uint8_t* out = (uint8_t*)line;
  uint8_t total = min(size, RingBufferDmaU8_available(ring));
  for (uint16_t i = 0; i < total; i++) {
    uint8_t c = *in++;
    *out = c;
    if (in >= ring->buffer + ring->size) {
      in -= ring->size;
    }
    if (c == '\n' || c == '\r') {
      *out = 0x00;
      ring->tailPtr = in;
      return true;
    }
    out++;
  }
  return false;
}

uint8_t RingBufferDmaU8_read(RingBufferDmaU8* ring) {
  uint8_t ret = *ring->tailPtr++;
  if (ring->tailPtr >= ring->buffer + ring->size) {
    ring->tailPtr -= ring->size;
  }
  return ret;
}

#endif