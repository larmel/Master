#include <stdlib.h>
#include <stdio.h>

#define N 65536

// Weird effects, watwat. Only some times counts cycles...
// perf stat -e r02a3:u,r02a3:u,r02a3:u,r02a3:u,r02a3:u,r02a3:u,r02a3:u,instructions:u,cycles:u ./a.out 1

/**
 * Program using as many counters as possible.
 * Goal: Find out which counters misbehave when run several times at once.
 * Observation initially: three "groups" of measurements, large gaps.
 */

int main(int argc, char **argv)
{
	int offset = atoi(argv[1]), i; 
	//printf("Offset: %d\n", offset);
	int *a = malloc(N*sizeof(int));
	int *b = malloc(2*N*sizeof(int));

	for (i = 0; i < N; ++i, ++offset)
	{
		a[i] += 1;
		b[offset] += 1;
	}

	//printf("Heap location: %p, %p\n", a, b);

	return 0;
}

