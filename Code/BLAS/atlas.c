#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

// M * N sized matrix A
#define M 0x1000
#define N 0x1000

int main()
{
	const double alpha = 1.0;
	const double beta  = 0.0;

	double *A = malloc(sizeof(double) * (M * N + 0x100));
	double *x = malloc(sizeof(double) * M);
	double *y = malloc(sizeof(double) * M);

	//A += 0x100;
	printf("A, x, y : (%p, %p, %p)\n", A, x, y);

	for (int i=0; i<M; ++i) {
		x[i] = M - i;
		for (int j=0; j<N; ++j) 
		{
			A[i*M+j] = i*M+j;
			//printf("%5.1f", A[i*M+j]);
		}	
		//putchar('\n');
	}

	// y = Ax * alpha
	cblas_dgemv(CblasRowMajor, CblasTrans, M, N, alpha, A, M, x, 1, beta, y, 1);

	//for (int i=0; i<M; ++i)
	//	printf("%5.1f\n", y[i]);

	return 0;
}
