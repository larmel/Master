#include <stdlib.h>
#include <stdio.h>

// For automated testing, set -DOFFSET
#ifndef OFFSET
    #define OFFSET 0x00
#endif

#define N 0x100000
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

int main(int argc, char **argv)
{
    // Needed for automated test script. Just want to run all performance counters
    // to find cause of very odd resource stall spike.
    int offset = atoi(argv[1]);

    float *input  = malloc( N          * sizeof(float));
    float *result = malloc((N + 0x100) * sizeof(float));

    convolve(N, input, (result + offset));

    printf("Offset: %d : (%p, %p)\n", offset, input, result);

    return 0;
}
