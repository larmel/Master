#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

#define M 8192
#define N 1
#define K 8192

/**
 * Matrix-matrix multiplication
 */
int main(int argc, char **argv)
{
    const double alpha = 1.0;
    const double beta  = 0.0;

    // op(A) = M x K , op(B) = K x N, C = M x N
    //void* foo = malloc(sizeof(double) * 0x800);
    double *A = malloc(sizeof(double) * M*K);
    double *B = malloc(sizeof(double) * K*N);
    double *C = malloc(sizeof(double) * M*N);

    printf("A, B, C : (%p, %p, %p)\n", A, B, C);

    // Compute C = alpha*(A*B') + beta*C
    // http://software.intel.com/sites/products/documentation/hpc/mkl/mklman/GUID-97718E5C-6E0A-44F0-B2B1-A551F0F164B2.htm
    // 'Leading dimension' = cols for RowMajor and rows for ColMajor
    for (int i = 0; i < 10; ++i)
    cblas_dgemm(CblasColMajor, 
        CblasNoTrans, // Transpose A
        CblasNoTrans, // Transpose B
        M, N, K,
        alpha,
        A, M,         // A, leading dimension in op(A)
        B, K,         // B, leading dimension in op(B)
        beta,
        C, K
    );

    //free(A), free(B), free(C);
    return 0;
}
