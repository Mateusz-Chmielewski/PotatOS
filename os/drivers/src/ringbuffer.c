#include "ringbuffer.h"

void ringbuffer_init(ringbuffer_t *rb, uint8_t *buffer, uint32_t size) {
  rb->buffer = buffer;
  rb->mask = size - 1;
  rb->read_pos = 0;
  rb->write_pos = 0;
}

bool ringbuffer_empty(ringbuffer_t *rb) {
  return rb->read_pos == rb->write_pos;
}

bool ringbuffer_read(ringbuffer_t *rb, uint8_t *data) {
  uint32_t local_read_pos = rb->read_pos;
  uint32_t local_write_pos = rb->write_pos;

  if (local_read_pos == local_write_pos) {
    return false;
  }

  *data = rb->buffer[local_read_pos];
  local_read_pos =
      (local_read_pos + 1) &
      rb->mask; // Increment read position and wrap around if necessary
  rb->read_pos = local_read_pos;
  return true;
}

bool ringbuffer_write(ringbuffer_t *rb, uint8_t data) {
  uint32_t local_write_pos = rb->write_pos;
  uint32_t local_read_pos = rb->read_pos;
  uint32_t next_write_pos = (local_write_pos + 1) & rb->mask;

  if (next_write_pos == local_read_pos) {
    return false;
  }

  rb->buffer[local_write_pos] = data;
  rb->write_pos = next_write_pos;
  return true;
}