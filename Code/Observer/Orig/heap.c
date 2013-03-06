#include <stdlib.h>
#include <stdio.h>

#define N 65536

int main(int argc, char **argv)
{
	int offset = atoi(argv[1]), i; 
	printf("Offset: %d\n", offset);
	int *a = malloc(N*sizeof(int));
	int *b = malloc(2*N*sizeof(int));

	for (i = 0; i < N; ++i, ++offset)
	{
		a[i] += 1;
		b[offset] += 1;
	}

	printf("Heap location: %p, %p\n", a, b);

	return 0;
}

