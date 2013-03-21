#include <stdio.h>

// objdump -S a.out > a.obj; objdump -S b.out > b.obj; clear; diff a.obj b.obj

int factorialxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx(int n)
{
    int r = n;
    if (r > 1)
        while (--n)
            r *= n;
    return r;
}

int sum(int n)
{
    return n * (n - 1) / 2;
}


int main(int argc, char **argv)
{
    int n = (argc > 1) ? atoi(argv[1]) : 42;
    n = factorialxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx(n) - sum(n);
    printf("n = %d\n", n);
    return n;
}


