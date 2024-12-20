#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct RingBuffer {
  uint8_t *buffer;
  uint32_t mask;
  uint32_t read_pos;
  uint32_t write_pos;
} RingBuffer;

void ringbuffer_init(RingBuffer *rb, uint8_t *buffer, uint32_t size);
bool ringbuffer_empty(RingBuffer *rb);
bool ringbuffer_write(RingBuffer *rb, uint8_t data);
bool ringbuffer_read(RingBuffer *rb, uint8_t *data);

#endif // RINGBUFFER_H
