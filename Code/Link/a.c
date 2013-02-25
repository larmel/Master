#include <stdio.h>

static int a = 0;

int foo()
{
	int n = 0;
	while (n < 100)
	{
		n++;
		a += n;
		a += n;
		a += n;
		a += n;
	}
	//puts("Hello from foo");
	return 42;
}
