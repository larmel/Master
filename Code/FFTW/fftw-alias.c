#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <unistd.h>

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

//#define MAX_OFFSET 0xf00
#ifndef N
    #define N 16 //524288 // 8 73 75 76 80 103
#endif
#ifndef X
    #define X 200000
#endif

// 0xef for -n 16

int main(int argc, char **argv)
{
    int n = N, x = X, i;
    long offset = atoi(argv[1]);
    fftw_complex *in  = NULL;
    fftw_complex *temp = NULL, *temp2 = NULL;
    fftw_complex *out = NULL;
    fftw_plan p;

    temp2 = fftw_malloc(sizeof(fftw_complex) * 0);
    in    = fftw_malloc(sizeof(fftw_complex) * n);
    temp  = fftw_malloc(sizeof(fftw_complex) * 32);
    out   = fftw_malloc(sizeof(fftw_complex) * n);

    for (i = 0; i < n; ++i) {
        in[i][0] = i;
        in[i][1] = i;
    }
    p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    //fftw_print_plan(p);
    //putchar('\n');

    asm volatile (
        "movq  %%rsp, %0;"
        "andq  $-1024, %%rsp;"
        : "=r"(offset)
        : 
        :
        );

    for (i = 0; i < x; ++i)
    {
        fftw_execute(p);
    }

    asm volatile (
        "movq   %0, %%rsp;"
        :  
        : "r"(offset)
        :
        );

    fftw_destroy_plan(p);

    // Printf result for verification
    //for (i = 0; i < n; ++i)
    //    printf("(%f, %f), ", out[i][0], out[i][1]);
    //putchar('\n');

    printf("in: %p, out: %p\n", in, out);

    fftw_free(in), fftw_free(out); //fftw_free(out - offset);

    return 0;
}
