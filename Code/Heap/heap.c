#include <stdlib.h>
#include <stdio.h>

#define N 8

int a[N][N];
int r[N][N];

int main()
{
	int** heap = malloc(sizeof(int*)*N);
	int i, j, k, s;
	for (i = 0; i < N; ++i)
		heap[i] = malloc(sizeof(int)*N);

	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			s = 0;
			for (k = 0; k < N; ++k)
				s += heap[k][j] * a[i][k];
			r[i][j] = s;
		}
	}

	/*for (i = 0; i < N; ++i) {
		heap[i] = 0;
		stack[i] = 0;
	}*/

	//printf("Stack location: %p\n", stack);
	printf("Heap location:  %p : %p, %p, %p, %p\n", heap, heap[0], heap[1], heap[2], heap[3]);

	return 0;
}

