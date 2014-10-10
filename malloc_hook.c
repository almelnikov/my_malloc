#include <malloc.h>
#include "my_malloc.h"

#define MIN_BLOCK 91
#define MAX_BLOCK (91*4)

/*
#define MIN_BLOCK 0
#define MAX_BLOCK ULONG_MAX
*/

static void my_init_hook (void);
static void *my_malloc_hook (size_t, const void *);
static void my_free_hook (void*, const void *);

static void *(*old_malloc_hook) (size_t, const void *);
static void (*old_free_hook) (void*, const void *);

void (* volatile __malloc_initialize_hook) (void) = my_init_hook;

static void my_init_hook (void)
{
	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;
	__malloc_hook = my_malloc_hook;
	__free_hook = my_free_hook;
}

static void *my_malloc_hook (size_t size, const void *caller)
{
	void *result;
	int range_flag = 0;;

	/* Restore all old hooks */
	__malloc_hook = old_malloc_hook;
	__free_hook = old_free_hook;
	/* Call recursively */
	if ((size >= MIN_BLOCK) && (size <= MAX_BLOCK))
		result = my_malloc(size);
	else {
		range_flag = 1;
		result = NULL;
	}
	/* Save underlying hooks */
	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;
	/* printf might call malloc, so protect it too. */
	printf("malloc (%u) returns %p\n", (unsigned int) size, result);
	if (range_flag != 0)
		printf("Block size is out of range!\n");
	/* Restore our own hooks */
	__malloc_hook = my_malloc_hook;
	__free_hook = my_free_hook;
	return result;
}

static void my_free_hook (void *ptr, const void *caller)
{
	/* Restore all old hooks */
	__malloc_hook = old_malloc_hook;
 	__free_hook = old_free_hook;
	my_free(ptr);
	/* Save underlying hooks */
	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;
	/* printf might call free, so protect it too. */
	printf("freed pointer %p\n", ptr);
	/* Restore our own hooks */
	__malloc_hook = my_malloc_hook;
	__free_hook = my_free_hook;
}

int main(int argc, char *argv[])
{
	int *ptrs[200], *ptr;
	int i;

	if (argc >= 2) {
		sscanf(argv[1], "%llu", &max_heap_size);
	}
	for (i = 0; i < 200; i++) {
		ptrs[i] = malloc((MIN_BLOCK + i*10) % MAX_BLOCK);
	}
	free(ptrs[13]);
	ptrs[13] = NULL;
	free(ptrs[12]);
	ptrs[12] = NULL;
	free(ptrs[11]);
	ptrs[11] = NULL;
	my_malloc_print();
	for (i = 0; i < 200; i++) {
		free(ptrs[i]);
	}
	my_malloc_print();
	return 0;
}