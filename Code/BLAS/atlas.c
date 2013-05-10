#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

#define M 8192
#define N 1
#define K 8192

/**
 * Matrix-matrix multiplication
 */
void mm()
{
	const double alpha = 1.0;
	const double beta  = 0.0;

	// op(A) = M x K , op(B) = K x N, C = M x N
	double *A = malloc(sizeof(double) * (M*K + 0x100));
	double *B = malloc(sizeof(double) * K*N);
	double *C = malloc(sizeof(double) * M*N);

	//A += 0x100;
	printf("A, B, C : (%p, %p, %p)\n", A, B, C);

	// Compute C = alpha*(A*B') + beta*C
	// http://software.intel.com/sites/products/documentation/hpc/mkl/mklman/GUID-97718E5C-6E0A-44F0-B2B1-A551F0F164B2.htm
	cblas_dgemm(CblasRowMajor, 
		CblasNoTrans, // Transpose A
		CblasNoTrans,   // Transpose B (resulting in a nop, B'')
		M, N, K,
		alpha,
		A, K,		  // A, cols in op(A)
		B, N,		  // B, cols in op(B)
		beta,
		C, N
	);

	free(A), free(B), free(C);
}

/**
 * Matrix-vector multiplication
 */
void mv()
{
	const double alpha = 1.0;
	const double beta  = 0.0;

	char *fill = malloc(sizeof(char) * 0x40);

	double *A = malloc(sizeof(double) * M * K);
	double *x = malloc(sizeof(double) * K);
	double *y = malloc(sizeof(double) * K);

	printf("A, x, y : (%p, %p, %p)\n", A, x, y);

	// y = Ax * alpha
	cblas_dgemv(CblasRowMajor, 
		CblasTrans, 
		M, K, 
		alpha, 
		A, K, 
		x, 1, 
		beta, 
		y, 1
	);
}

int main()
{
	//mm();
	mv();
	return 0;
}
