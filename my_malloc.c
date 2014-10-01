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

static block_t *extend_heap(block_t *last, size_t size)
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

static int check_block_size(block_t *ptr, size_t size) {
	block_t *newblock;

	if ((ptr->free != 0) || (ptr->size < size))	
		return 0;
	ptr->free = 1;
	if ((size + MINIMAL_BLOCK) <= ptr->size) {
		newblock = (block_t*)((void*)ptr + HEADER_SIZE + size);
		newblock->free = 0;
		neblock->size = ptr-> size - HEADER_SIZE - size;
		newblock->next = ptr->next;
		newblock->prev = ptr;
		ptr->next = newblock;
	}
	return 1;
}

void *my_malloc(size_t size)
{
	block_t *tmp, *last;
	void *ptr;
	int block_notfound = 0;
	
	if (base != NULL)
		for (tmp = base; tmp->next != NULL; tmp = tmp->next) {
			
		}
	else
		tmp = NULL;
	if (block_notfound == 0) {
		last = extend_heap(tmp, size);
		if (base == NULL)
			base = last;
		else
			tmp->next = last;
	}
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
			s->prev->size += s->size + HEADER_SIZE;
			s->prev->next = s->next;
			if (s->next != NULL)
				s->next->prev = s->prev;
		}
	}
}

void my_malloc_print()
{
	block_t *ptr;
	
	for (ptr = base; ptr != NULL; ptr = ptr->next) {
		printf("prev=%X next=%X size=%d\n", ptr->prev, ptr->next, ptr->size);
	}
}