#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include "immintrin.h"

// make clean; make a.out; ./a.out 1

#define N 0x7ffa // 65536 = 0x10000
#define ALIAS(a, b) (((long)a & 0xfff) == ((long)b & 0xfff))

volatile static int inc = 0;

int main(int argc, char **argv)
{
	int alpha = 42;
	int offset = atoi(argv[1]), i; 
	int *inc_ptr = &inc;
	//printf("Offset: %d\n", offset);
	//int *a = malloc(N*sizeof(int));
	//int *b = malloc(N*sizeof(int)); // About 250 000 cycles. Dwarfs the rest
	//while (i % 2 == 0 && (long)b & 0xfff != (long)a & 0xfff)
	//	b++;

	volatile int one = 1;

	int *a = malloc(N*sizeof(int));
	int *fill = malloc(offset*sizeof(int));
	int *b = malloc(N*sizeof(int));
	int *fill2 = malloc(offset*sizeof(int));
	int *c = malloc(N*sizeof(int));
	int *fill3 = malloc(offset*sizeof(int));
	int *d = malloc(N*sizeof(int));
	int *fill4 = malloc(offset*sizeof(int));
	int *e = malloc(N*sizeof(int));
	//printf("%d\n", N);

	// Lowest start address of heap: 0x00602000
	//int *addr = (int*)a + 2*N*sizeof(int) + 0x2000 + offset;
	//int *map = mmap((void*)addr, N*sizeof(int), PROT_READ | PROT_WRITE,  MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	//if (map == MAP_FAILED)
	//{
	//	printf("Failed mmap\n");
	//	return 0;
	//}

	//printf("Address a:    %p\n", a);
	//printf("Address fill: %p\n", fill);
	//printf("Address b:    %p\n", b);

	int t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	if (ALIAS(a, b) && ALIAS(b, c) && ALIAS(c, d) && ALIAS(d, e))
		printf("Address alias on offset %d\n", offset);
	__m256* tmp = (__m256*)&a[0];
	*tmp = _mm256_rsqrt_ps(*tmp);

	for (i = 16; i < N-16; ++i)
	{
		//*inc_ptr += 1;
		//alpha += inc;
		//int foo = inc;
		//__m256* tmp = (__m256*)&a[i];
		//*tmp = _mm256_rsqrt_ps(*tmp);
		/*b[i] += inc;
		c[i] += inc;
		d[i] += inc;
		e[i] += inc;*/
	}

/*
	for (i = 0; i < N; ++i, ++offset)
	{
		alpha += inc;
		//a[i] = alpha*a[i] + b[i-1];
		b[i] += inc;
	}
*/
	//printf("Heap location: %p, %p\n", a, b);

	return a[one] + b[one];
}

