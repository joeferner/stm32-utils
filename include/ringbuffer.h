
#ifndef _STM32LIB_RINGBUFFER_H_
#define _STM32LIB_RINGBUFFER_H_

#include <stdint.h>

typedef struct {
  uint8_t* storage;
  uint8_t* end;
  uint16_t size;
  volatile uint8_t* read;
  volatile uint8_t* write;
  volatile uint16_t available;
} RingBufferU8;

void RingBufferU8_init(RingBufferU8* ring, uint8_t* storage, uint16_t size);
uint16_t RingBufferU8_available(RingBufferU8* ring);
uint16_t RingBufferU8_free(RingBufferU8* ring);
void RingBufferU8_clear(RingBufferU8* ring);
void RingBufferU8_read(RingBufferU8* ring, uint8_t* buffer, uint16_t size);
uint8_t RingBufferU8_readByte(RingBufferU8* ring);
void RingBufferU8_write(RingBufferU8* ring, const uint8_t* buffer, uint16_t size);
void RingBufferU8_writeByte(RingBufferU8* ring, uint8_t b);
uint16_t RingBufferU8_readUntil(RingBufferU8* ring, char* buffer, uint16_t size, uint8_t stopByte);
uint16_t RingBufferU8_readLine(RingBufferU8* ring, char* buffer, uint16_t size);
uint8_t RingBufferU8_peek(RingBufferU8* ring);
uint8_t RingBufferU8_peekn(RingBufferU8* ring, uint16_t i);

#endif
