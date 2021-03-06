#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>

#ifndef DEBUG
    #define DEBUG 0
#endif
#ifndef PLAN
    #define PLAN FFTW_ESTIMATE
#endif
#ifndef N
    #define N 16
#endif
#ifndef X
    #define X 200000
#endif

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    char *fill = malloc(sizeof(char) * n);
    fftw_complex *in  = fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *out = fftw_malloc(sizeof(fftw_complex) * N);

    fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, PLAN);

    // FFTW_ESTIMATE overwrites input data, initialize after planning
    for (int i = 0; i < N; ++i)
        in[i][0] = i, in[i][1] = i;

#ifdef MAINFIX
    void *rsp;
    __asm__ volatile (
        "movq  %%rsp, %0;"
        "andq  $-4096, %%rsp;"
        : "=r"(rsp)
        : 
        :
        );
#endif

    for (int i = 0; i < X; ++i)
        fftw_execute(p);

#ifdef MAINFIX
    __asm__ volatile (
        "movq   %0, %%rsp;"
        :  
        : "r"(rsp)
        :
        );
#endif

#if (DEBUG)
    fftw_print_plan(p);
    printf(" in: %p, out: %p\n", in, out);
    for (int i = 0; i < N; ++i)
        printf("(%f, %f), ", out[i][0], out[i][1]);
    putchar('\n');
#endif

    fftw_destroy_plan(p);
    fftw_free(in), fftw_free(out);
    return 0;
}