#include "my_malloc.h"

int main()
{
	char *str, *str2;
	int *arr[10], i;
	
	str = (char *)my_malloc(10);
	strcpy(str, "Hello!\n");
	printf("%s", str);
	str2 = (char *)my_malloc(100);
	strcpy(str2, "Hello allocation!\n");
	printf("%s", str2);
	//my_free(str);
	//my_free(str2);
	for (i = 0; i < 10; i++) {
		arr[i] = my_malloc(sizeof(int));
		*arr[i]	= i;
	}
	for (i = 0; i < 10; i++)
		printf("%d\n", *arr[i]);
	return 0;
}