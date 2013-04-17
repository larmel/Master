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

#define MAX_OFFSET 0xf00
#ifndef N
    #define N 16 // 8 73 75 76 80 103
#endif
#ifndef X
    #define X 200000
#endif

// 0xef for -n 16

int main(int argc, char **argv)
{
    int n = N, x = X;
    int offset = atoi(argv[1]), i;
    fftw_complex *in  = NULL;
    fftw_complex *out = NULL;
    fftw_plan p;

    in  = fftw_malloc(sizeof(fftw_complex) * n);
    out = fftw_malloc(sizeof(fftw_complex) * (n + MAX_OFFSET));
    out += offset;

    for (i = 0; i < n; ++i) {
        in[i][0] = rand() - RAND_MAX/2;
        in[i][1] = rand() - RAND_MAX/2;
    }

    p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    for (i = 0; i < x; ++i)
        fftw_execute(p);

    fftw_destroy_plan(p);

    printf("fftw\tn=%d\tx=%d\tstack=%p\t(%p, %p)\n", n, x, &i, in, out);

    fftw_free(in), fftw_free(out - offset);

    return 0;
}
