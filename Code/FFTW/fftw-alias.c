#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>

// Based on code provided in KISSFFT
#ifdef DATATYPEfloat
    #define fftw_complex      fftwf_complex
    #define fftw_plan         fftwf_plan
    #define fftw_plan_dft_1d  fftwf_plan_dft_1d
    #define fftw_execute      fftwf_execute
    #define fftw_destroy_plan fftwf_destroy_plan
    #define fftw_malloc       fftwf_malloc
    #define fftw_free         fftwf_free
#endif

#define DEBUG 0

#ifndef N
    #define N 16
#endif
#ifndef X
    #define X 200000
#endif

// 0xef for -n 16

int main(int argc, char **argv)
{
    fftw_complex *in  = fftw_malloc(sizeof(fftw_complex) * N);
#ifdef MODIFIED
    int n = atoi(argv[1]);
    char *fill = malloc(sizeof(char) * n);
#endif
    fftw_complex *out = fftw_malloc(sizeof(fftw_complex) * N);

    for (int i = 0; i < N; ++i)
        in[i][0] = i, in[i][1] = i;

    fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    /*void *rsp;
    __asm__ volatile (
        "movq  %%rsp, %0;"
        "andq  $-4096, %%rsp;"
        : "=r"(rsp)
        : 
        :
        );*/

    for (int i = 0; i < X; ++i)
        fftw_execute(p);

    /*__asm__ volatile (
        "movq   %0, %%rsp;"
        :  
        : "r"(rsp)
        :
        );*/

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
