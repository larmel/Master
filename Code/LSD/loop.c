//#include <stdio.h>
//#include <inttypes.h>

// rip assembly taken from http://stackoverflow.com/questions/11723836/instruction-pointer-and-function-pointer-constantness
//
// cc align.s; perf stat -e cycles:u,r0120:u,r01a8:u ./a.out
// cc align.c -S; cc align.s; objdump -S a.out; perf stat -e cycles:u,r0120:u,r01a8:u ./a.out
//
// Shared library
// cc -c -fPIC loop.c - loop.o
// cc -shared -Wl,-soname,libloop.so -o libloop.so loop.o
//
// objdump -S shows that the last 12 bits of .so code addresses are statically determined :(
// Static linking seems to be the same as link order. Everything is determined at link time.
//
// cc -O3 lsd.c loop-optimized.c fact.c -o c.out; perf stat -e cycles:u,r0120:u,r01a8:u,branch-misses:u ./c.out

#define B22(n) b += i*i*a + 1

volatile int i = 42;

int loop(int a)
{
    register int b = i == 42 ? 1 : 0;
    do {
        if (!i) B22(1); // mov (6), test (2), jne (2) => 10
        if (!i) B22(2);
        if (!i) B22(3);
        if (!i) B22(4);
        if (!i) B22(5);
        if (!i) B22(6);
        if (!i) B22(7);
        if (!i) B22(8);
        if (!i) B22(9);
        if (!i) B22(10);
        if (!i) B22(11);
        // 27 bytes for increment and test
    } while (i++ < 0x12345678); // 0x12345678
    return b;
}
/*
int main()
{
    return loop(10);
}*/