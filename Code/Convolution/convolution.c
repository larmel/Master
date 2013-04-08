#include <stdlib.h>
#include <stdio.h>

// Hoard:    export LD_PRELOAD=~/Allocators/Hoard/libhoard.so
// tcmalloc: libgoogle-perftools-dev, -ltcmalloc
// cc -O3 convolution.c; cc -O3 convolution.c -S; perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./a.out
// Best result with -O3 -std=c99 -march=native and no offset
// -- Then we can save 250k alias and 300k RS with +0x30. Exact same instruction count (but sometimes slightly higher?)

#define N 0x100000
static float kernel[5] = {0.1, 0.25, 0.3, 0.25, 0.1};

void convolve(int size, float * restrict input, float * restrict output)
{
    int i, j;
    for (i = 2; i < size - 2; ++i)
    {
        output[i] = 0;
        for (j = 0; j < 5; ++j)
            output[i] += input[i-2+j] * kernel[j];
    }
}

int main(void)
{
    float *input  = malloc( N         * sizeof(float));
    float *result = malloc((N + 0xf0) * sizeof(float));

    convolve(N, input, (result + 0x00));

    printf("input, result : (%p, %p)\n", input, result);

    return 0;
}
