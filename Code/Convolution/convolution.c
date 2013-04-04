#include <stdlib.h>
#include <stdio.h>

#define N 0xffff

// cc -O3 convolution.c; cc -O3 convolution.c -S; perf stat -e cycles:u,r0107:u,r01a2:u -r 5 ./a.out

static float kernel[5] = {0.1, 0.25, 0.3, 0.25, 0.1};

void convolve(float *input, float *output, int size)
{
    int i;
    float res;
    for (i = 2; i < size - 2; ++i)
    {
        // Read and write to arrays to generate lots of conflicts
        output[i] = input[i-2]*kernel[0];
        output[i] += input[i-1]*kernel[1];
        output[i] += input[i]*kernel[2];
        output[i] += input[i+1]*kernel[3];
        output[i] += input[i+2]*kernel[4];
    }
}

int main(void)
{
    float *input  = malloc(N*sizeof(float));
    float *result = malloc((N+0x10)*sizeof(float));

    convolve(input, (result + 0x10), N);

    printf("input, result : (%p, %p)\n", input, result);

    return 0;
}

