#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>

#define PAGE 0x1000
#define SIZE 2*PAGE


void foo(double* a, double* b)
{
	__m256d t;
	for (int i = 2; i < SIZE-400; i += PAGE) {
		t = _mm256_loadu_pd(&a[i]);
		_mm256_storeu_pd(&b[i], t);
	}
}

/**
 * Goal: get varying number of page faults based on rome environment cause
 * Hopefully incur a significant cost. Possibly detectable runtime/compile-time
 *
 * Intrinsig unaligned load/store
 *  vmoveu... <- Unaligned
 *  vmovea... <- Aligned 
 *
 * http://stackoverflow.com/questions/5983389/how-to-align-stack-at-32-byte-boundary-in-gcc?rq=1
 */
int main()
{
	double *a = malloc(SIZE * sizeof(double));
	double *b = malloc(SIZE * sizeof(double));

	foo(a, b);
	foo(b, a);

	printf("%f\n", b[SIZE-1]);

	return 0;
}

