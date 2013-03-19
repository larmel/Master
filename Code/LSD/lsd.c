#include <stdio.h>

// make clean; clear; make test
int main()
{
    int i = loop(10);
    int f = fact(10);

    printf("Loop: %d\n", i);
    printf("Fact: %d\n", f);

    return 0;
}

