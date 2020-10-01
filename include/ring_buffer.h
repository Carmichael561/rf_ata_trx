#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#define RB_CHUNK_SIZE_32 32
#define RB_CHUNK_SIZE_16 16
#define RB_CHUNKS 128

typedef struct ring_buff_t {
	uint8_t *buffer;
	size_t  head;
	size_t  tail;
	size_t  size;
	bool    full;
} ring_buff_t;

int ring_buffer_init(ring_buff_t *rb, size_t size);

void ring_buffer_free(ring_buff_t *rb);

int ring_buffer_queue(ring_buff_t *rb, uint8_t data);

int ring_buffer_dequeue(ring_buff_t *rb, uint8_t *data);

bool ring_buffer_empty(ring_buff_t *rb);

uint8_t* ring_buffer_reserve(ring_buff_t *rb, uint32_t size);

#endif
