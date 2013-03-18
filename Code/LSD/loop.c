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

#define B27 a = b, a = b, a = b, a = b, a = b, a = b, a = b, a = b, a = b

int loop()
{
    //uint64_t ip;
    register int i = 0, a = 1, b = 1;
    while (i++ < 0x12345678) // 0x12345678
    {
        // 3b + 2B cmp and je, 9*3B dead
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
        if (a != b) B27;
    }
    //asm("leaq (%%rip), %0;": "=r"(ip));
    //printf("rip is 0x%016" PRIx64 "\n", ip);
    return i;
}