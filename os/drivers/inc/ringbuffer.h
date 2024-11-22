#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct ringbuffer_t
{
  uint8_t *buffer;
  uint32_t mask;
  uint32_t read_pos;
  uint32_t write_pos;
} ringbuffer_t;

void ringbuffer_init(ringbuffer_t *rb, uint8_t *buffer, uint32_t size);
bool ringbuffer_empty(ringbuffer_t *rb);
bool ringbuffer_write(ringbuffer_t *rb, uint8_t data);
bool ringbuffer_read(ringbuffer_t *rb, uint8_t *data);

#endif // RINGBUFFER_H