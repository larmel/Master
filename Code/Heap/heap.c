#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

// make clean; make a.out; ./a.out 1

#define N 0x7ffa // 65536 = 0x10000

volatile static int inc = 0;

int main(int argc, char **argv)
{
	int alpha = 42;
	int offset = atoi(argv[1]), i; 
	int *inc_ptr = &inc;
	//printf("Offset: %d\n", offset);
	//int *a = malloc(N*sizeof(int));
	//int *b = malloc(N*sizeof(int)); // About 250 000 cycles. Dwarfs the rest
	//while (i % 2 == 0 && (long)b & 0xfff != (long)a & 0xfff)
	//	b++;

	volatile int one = 1;

	int *a = malloc(N*sizeof(int));
	int *fill = malloc(offset*sizeof(int));
	int *b = malloc(N*sizeof(int));
	//printf("%d\n", N);

	// Lowest start address of heap: 0x00602000
	//int *addr = (int*)a + 2*N*sizeof(int) + 0x2000 + offset;
	//int *map = mmap((void*)addr, N*sizeof(int), PROT_READ | PROT_WRITE,  MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	//if (map == MAP_FAILED)
	//{
	//	printf("Failed mmap\n");
	//	return 0;
	//}

	//printf("Address a:    %p\n", a);
	//printf("Address fill: %p\n", fill);
	//printf("Address b:    %p\n", b);

	for (i = 0; i < N; ++i)
	{
		//*inc_ptr += 1;
		//alpha += inc;
		//int foo = inc;
		a[i] += inc;
		b[i] += inc;
		a[i] += inc;
		b[i] += inc;
	}

/*
	for (i = 0; i < N; ++i, ++offset)
	{
		alpha += inc;
		//a[i] = alpha*a[i] + b[i-1];
		b[i] += inc;
	}
*/
	//printf("Heap location: %p, %p\n", a, b);

	return a[one] + b[one];
}

