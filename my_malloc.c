#include "my_malloc.h"

struct block_s {
	struct block_s *next;
	struct block_s *prev;
	char free;
	char payload[0];
};

typedef struct block_s block_t;

block_t *base = NULL;

static block_t *create_block(size_t s)
{
	block_t *tmp = NULL;
	
	tmp = (block_t *)sbrk(0);
	if (sbrk(HEADER_SIZE + s) == NULL)
		return NULL;
	else {
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->free = 1;
		memset(((char *)tmp) + s, 0, s);
	}
}

block_t *extend_heap(block_t *last, size_t size)
{
	block_t *tmp;
	
	tmp = (block_t *)sbrk(0);
	if (sbrk(HEADER_SIZE + size) == NULL)
		return NULL;
	else {
		tmp->next = NULL;
		tmp->prev = last;
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
	if (ptr != last)
		return ((void*)last + HEADER_SIZE);
	else
		return NULL;
}

void my_free(void *ptr)
{

}