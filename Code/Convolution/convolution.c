#include <stdlib.h>
#include <stdio.h>

// cc -O3 convolution.c; cc -O3 convolution.c -S; perf stat -e cycles:u,r0107:u,r01a2:u,instructions:u -r 10 ./a.out

#define N 0x10000
static float kernel[5] = {0.1, 0.25, 0.3, 0.25, 0.1};

void convolve(int size, float *input, float *output)
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
    float *result = malloc((N + 0x10) * sizeof(float));

    convolve(N, input, (result + 0x10));

    //printf("input, result : (%p, %p)\n", input, result);

    return 0;
}
