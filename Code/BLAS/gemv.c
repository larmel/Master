#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

// A is M x N -> rows x cols.
#define M 8192
#define N 8192

/**
 * Matrix-vector multiplication, y = alpha*Ax + beta*y
 * As a relic from Fortran, BLAS prefers col-major order. 
 * When CblasNoTrans is set, an additional copy operation of A is done.
 */
int main(int argc, char **argv)
{
    int offset1 = argc > 1 ? atoi(argv[1]) : 0;
    int offset2 = argc > 2 ? atoi(argv[2]) : 0;
    int iters   = argc > 3 ? atoi(argv[3]) : 1;

    const double alpha = 1.0, beta = 0.0;

    if (offset1) malloc(sizeof(char) * offset1);

    double *A = malloc(sizeof(double) * M * N);
    double *x = malloc(sizeof(double) * N);

    if (offset2) malloc(sizeof(char) * offset2);

    double *y = malloc(sizeof(double) * M);

    printf("A, x, y : (%p, %p, %p)\n", A, x, y);

    for (int i = 0; i < iters; ++i)
    cblas_dgemv(CblasColMajor, 
        CblasNoTrans, // Transpose A
        M, N,         // rows, cols
        alpha, 
        A, M,         // lda (offset to next column with same row index)
        x, 1, 
        beta, 
        y, 1
    );

    free(A), free(x), free(y);

    return 0;
}
