#include "ring_buffer.h"

int ring_buffer_init(ring_buff_t *rb, size_t size)
{
	if (rb == NULL || rb->buffer != NULL)
		return -1;

	rb->buffer = (uint8_t*)malloc(size);
	if (!rb->buffer)
		return -1;
	rb->size = size;
	rb->head = 0;
	rb->tail = 0;
	rb->full = false;
	return 0;
}

void ring_buffer_free(ring_buff_t *rb)
{
	if (rb == NULL)
		return;
	if (rb->buffer != NULL)
		free(rb->buffer);
	rb->buffer = NULL;
}

int ring_buffer_queue(ring_buff_t *rb, uint8_t data)
{
	if (rb == NULL || rb->full)
		return -1;
	rb->buffer[rb->head] = data;
	++rb->head;
	rb->head %= rb->size;
	rb->full = rb->head == rb->tail;
	return 0;
}

int ring_buffer_dequeue(ring_buff_t *rb, uint8_t *data)
{
	if (rb == NULL)
		return -1;
	if (!rb->full && rb->head == rb->tail)
		return -1;
	*data = rb->buffer[rb->tail];
	++rb->tail;
	rb->tail %= rb->size;
	rb->full = rb->head == rb->tail;
	return 0;
}

bool ring_buffer_empty(ring_buff_t *rb)
{
	return rb->full || (rb->head != rb->tail);
}

uint8_t* ring_buffer_reserve(ring_buff_t *rb, uint32_t size)
{
	uint8_t *head;
	head = (rb->head + size) % rb->size;
	if (rb == NULL || rb->full || head <= rb->head)
		return NULL;
	rb->head = head;
	return head;
}
