#include "my_malloc.h"

struct block_s {
	struct block_s *next;
	struct block_s *prev;
	size_t size;
	char free;
	char payload[0];
};

typedef struct block_s block_t;

block_t *base = NULL;

block_t *extend_heap(block_t *last, size_t size)
{
	block_t *tmp;
	
	tmp = (block_t *)sbrk(0);
	if (sbrk(HEADER_SIZE + size) == NULL)
		return NULL;
	else {
		tmp->next = NULL;
		tmp->prev = last;
		tmp->size = size;
		tmp->free = 1;
		memset(((char *)tmp) + size, 0, size);
		if (last != NULL)
			last = tmp;
	}
	
	return tmp;
}

void *my_malloc(size_t size)
{
	block_t *tmp, *last;
	void *ptr;
	
	if (base != NULL)
		for (tmp = base; tmp->next != NULL; tmp = tmp->next);
	else
		tmp = NULL;
	last = extend_heap(tmp, size);
	if (base == NULL)
		base = last;
	else
		tmp->next = last;
	if (last != NULL)
		return ((void*)last + HEADER_SIZE);
	else
		return NULL;
}

void my_free(void *ptr)
{
	block_t *s;
	
	if (ptr == NULL)
		return;
	
	s = (block_t*)(ptr - HEADER_SIZE);
	s->free = 0;
	if (s->next != NULL) {
		if (s->next->free == 0) {
			s->size += s->next->size + HEADER_SIZE;
			s->next = s->next->next;
			s->next->prev = s; 
		}
	}
	if (s->prev != NULL) {
		if (s->prev->free == 0) {
			s->size += s->prev->size + HEADER_SIZE;
			s->prev = s->prev->prev;
			s->prev->next = s;
		}
	}
}