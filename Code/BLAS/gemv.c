#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

// A is M x K -> rows x cols.
#define M 8192
#define K 8192

// Worstcase = 0x40, Bestcase = 0x400
#define OFFSET 0x0

/**
 * Matrix-vector multiplication, y = alpha*Ax + beta*y
 * As a relic from Fortran, BLAS prefers col-major order. 
 * When CblasNoTrans is set, an additional copy operation of A is done.
 */
int main(int argc, char **argv)
{
    int offset = argc > 1 ? atoi(argv[1]) : OFFSET;

    const double alpha = 1.0, beta = 0.0;

    void *fill = malloc(sizeof(char) * offset);

    double *A = malloc(sizeof(double) * M * K);
    double *x = malloc(sizeof(double) * K);
    double *y = malloc(sizeof(double) * M);

    printf("A, x, y : (%p, %p, %p)\n", A, x, y);

    //for (int i = 0; i < 1; ++i)
    cblas_dgemv(CblasColMajor, 
        CblasNoTrans, // Transpose A
        M, K, 		  // rows, cols
        alpha, 
        A, M, 		  // lda (offset to next column with same row index)
        x, 1, 
        beta, 
        y, 1
    );
	
	free(A), free(x), free(y), free(fill);

	return 0;
}

