#include "my_malloc.h"

int main()
{
	char *str, *str2;
	
	str = (char *)my_malloc(10);
	strcpy(str, "Hello!\n");
	str2 = (char *)my_malloc(100);
	strcpy(str2, "Hello allocation!\n");
	printf("%s", str);
	return 0;
}