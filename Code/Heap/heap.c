#include <stdlib.h>
#include <stdio.h>


int main()
{
	void* b = malloc(sizeof(char)*5000);
	void* a = malloc(sizeof(char)*50000000);

	printf("Heap location a: %p\n", a);
	printf("Heap location b: %p\n", b);
	return 0;
}

