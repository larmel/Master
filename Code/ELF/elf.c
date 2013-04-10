#include <stdio.h>

static long maxlong = 0xffffffff;

long fact(long n)
{
	if (n <= 1 || n >= maxlong)
		return 1;
	return fact(n-1) * n;
}

int main()
{
	long k = fact(8);

	printf("%ld\n", k);
	puts("This is a string");

	return 0;
}
