#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include "immintrin.h"

// make clean; make a.out; ./a.out 1

// Using simple code + optimization reduces to only register optimizations : No effects.

#define N 0x7ffa // 65536 = 0x10000
#define ALIAS(a, b) (((long)a & 0xfff) == ((long)b & 0xfff))

volatile static int inc = 0;

int main(int argc, char **argv)
{
    int alpha = 42;
    int offset = atoi(argv[1]), i, sum = 0;
    //printf("Offset: %d\n", offset);
    //int *a = malloc(N*sizeof(int));
    //int *b = malloc(N*sizeof(int)); // About 250 000 cycles. Dwarfs the rest
    //while (i % 2 == 0 && (long)b & 0xfff != (long)a & 0xfff)
    //  b++;

    //volatile int one = 1;

    float *a = malloc(N*sizeof(float));
    float *fill = malloc(offset*sizeof(float));
    float *b = malloc((N+1)*sizeof(float)); // Adding one messes up

    /*int *fill2 = malloc(offset*sizeof(int));
    int *c = malloc(N*sizeof(int));
    int *fill3 = malloc(offset*sizeof(int));
    int *d = malloc(N*sizeof(int));
    int *fill4 = malloc(offset*sizeof(int));
    int *e = malloc(N*sizeof(int));*/
    //printf("%d\n", N);

    // Lowest start address of heap: 0x00602000
    //int *addr = (int*)a + 2*N*sizeof(int) + 0x2000 + offset;
    //int *map = mmap((void*)addr, N*sizeof(int), PROT_READ | PROT_WRITE,  MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    //if (map == MAP_FAILED)
    //{
    //  printf("Failed mmap\n");
    //  return 0;
    //}

    //printf("Address a:    %p\n", a);
    //printf("Address fill: %p\n", fill);
    //printf("Address b:    %p\n", b);

    /*int t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    if (ALIAS(a, b) && ALIAS(b, c) && ALIAS(c, d) && ALIAS(d, e))
        printf("Address alias on offset %d\n", offset);*/

    //b = &b[16]; // Offset to avoid conflict

    if (ALIAS(a, b))
    {
        printf("Address alias on offset %d : (%p, %p)\n", offset, a, b);
    }
    else
    {
        printf("                 Offset %d : (%p, %p)\n", offset, a, b);
    }

    // a = a*x + b
    // b = 
    //for (j = 0; j < 10; ++j)
    for (i = 0; i < N-1; ++i)
    {
        b[i] += inc;
        b[i]++;
        b[i]++;
        b[i]++;
        //b[i]++;
        //sum += b[i];
        //{
            a[i]++;
            /*float tmp = a[i];
            tmp++;
            a[i] = tmp;*/
        //}
        //sum += a[i];
    }





    /*
    int i, j;
    float *a = malloc(N*sizeof(float));
    float *fill = malloc(offset*sizeof(float));
    float *b = malloc(N*sizeof(float));

    for (j = 0; j < 100; ++j)
    for (i = 0; i < N-16; ++i)
    {
        b[i] += inc;
        b[i]++;
        b[i]++;
        b[i]++;
        b[i]++;
        b[i]++;
        b[i]++;
        if (i % 4 == 0)
        {
            __m128 tmp = _mm_load_ps(&a[i]);
            tmp = _mm_sqrt_ps(tmp);
            _mm_store_ps(&a[i], tmp);
        }
    }*/

    return sum;
}

