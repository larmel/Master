#include <stdlib.h>
#include <stdio.h>

// For automated testing, set -DOFFSET
#ifndef OFFSET
    #define OFFSET 0x00
#endif

// Hoard:    export LD_PRELOAD=~/Allocators/Hoard/libhoard.so
// tcmalloc: libgoogle-perftools-dev, -ltcmalloc
// cc -O3 convolution.c; cc -O3 convolution.c -S; perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./a.out
// Best result with -O3 -std=c99 -march=native and no offset
// -- Then we can save 250k alias and 300k RS with +0x30. Exact same instruction count (but sometimes slightly higher?)

#define N 0x100000
static float kernel[5] = {0.1, 0.25, 0.3, 0.25, 0.1};

void convolve(int size, const float * restrict input, float * restrict output)
{
    int i, j;
    for (i = 2; i < size - 2; ++i)
    {
        output[i] = 0;
        for (j = 0; j < 5; ++j)
            output[i] += input[i-2+j] * kernel[j];
    }
}

int main(int argc, char **argv)
{
    // Needed for automated test script
    int offset = argc > 1 ? atoi(argv[1]) : 0, i = 0;

    float *input  = malloc( N          * sizeof(float));
    float *result = malloc((N + 0x100) * sizeof(float));

    //for (i = 0; i < 2; i++)
    convolve(N, input, (result + offset));

    printf("Offset: %d : (%p, %p)\n", offset, input, result);

    return 0;
}
