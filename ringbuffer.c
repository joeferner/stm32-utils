
#include "ringbuffer.h"
#include "utils.h"

void RingBufferU8_init(RingBufferU8 *ring, uint8_t *storage, uint16_t size) {
  ring->storage = storage;
  ring->size = size;
  ring->end = ring->storage + ring->size;
  ring->read = ring->storage;
  ring->write = ring->storage;
  ring->available = 0;
}

uint16_t RingBufferU8_available(RingBufferU8 *ring) {
  return ring->available;
}

uint16_t RingBufferU8_free(RingBufferU8 *ring) {
  return ring->size - ring->available;
}

void RingBufferU8_clear(RingBufferU8 *ring) {
  ring->read = ring->storage;
  ring->write = ring->storage;
  ring->available = 0;
}

uint8_t RingBufferU8_readByte(RingBufferU8 *ring) {
  if (ring->available == 0) {
    return 0;
  }
  uint8_t ret = *ring->read++;
  ring->available--;
  if (ring->read >= ring->end) {
    ring->read = ring->storage;
  }
  return ret;
}

void RingBufferU8_read(RingBufferU8 *ring, uint8_t *buffer, uint16_t size) {
  uint16_t i;

  // TODO can be optimized
  for (i = 0; i < size; i++) {
    buffer[i] = RingBufferU8_readByte(ring);
  }
}

void RingBufferU8_writeByte(RingBufferU8 *ring, uint8_t b) {
  if (ring->available >= ring->size) {
    RingBufferU8_readByte(ring);
  }

  *ring->write = b;
  ring->write++;
  ring->available++;
  if (ring->write >= ring->end) {
    ring->write = ring->storage;
  }
}

void RingBufferU8_write(RingBufferU8 *ring, const uint8_t *buffer, uint16_t size) {
  uint16_t i;

  // TODO can be optimized
  for (i = 0; i < size; i++) {
    RingBufferU8_writeByte(ring, buffer[i]);
  }
}

uint16_t RingBufferU8_readLine(RingBufferU8 *ring, char *buffer, uint16_t size) {
  return RingBufferU8_readUntil(ring, buffer, size, '\r');
}

uint16_t RingBufferU8_readUntil(RingBufferU8 *ring, char *buffer, uint16_t size, uint8_t stopByte) {
  uint8_t b;
  uint16_t i;
  for (i = 0; i < min(ring->available, size - 1); i++) {
    b = RingBufferU8_peekn(ring, i);
    if (b == stopByte) {
      i++;
      RingBufferU8_read(ring, (uint8_t *) buffer, i);
      buffer[i] = '\0';
      return i;
    }
  }
  buffer[0] = '\0';
  return 0;
}

uint8_t RingBufferU8_peek(RingBufferU8 *ring) {
  return RingBufferU8_peekn(ring, 0);
}

uint8_t RingBufferU8_peekn(RingBufferU8 *ring, uint16_t i) {
  if (i >= ring->available) {
    return 0;
  }

  uint8_t *read = (uint8_t *)ring->read;
  uint8_t *p = read + i;
  if (p >= ring->end) {
    p -= ring->size;
  }
  return *p;
}
