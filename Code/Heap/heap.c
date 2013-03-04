#include <stdlib.h>
#include <stdio.h>

#define N 65536 // 65536

static int inc = 0;

int main(int argc, char **argv)
{
	int alpha = 42;
	int offset = atoi(argv[1]), i; 
	int inc2;
	//printf("Offset: %d\n", offset);
	//int *a = malloc(N*sizeof(int));
	int *b = malloc(2*N*sizeof(int));
	//while (i % 2 == 0 && (long)b & 0xfff != (long)a & 0xfff)
	//	b++;

	for (i = 0; i < N; ++i, ++offset)
	{
		alpha += inc;
		//a[i] = alpha*a[i] + b[i-1];
		b[i] += inc;
	}

	//printf("Heap location: %p, %p\n", a, b);

	return 0;
}

