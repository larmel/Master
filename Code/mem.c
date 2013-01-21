#include <stdlib.h>
#include <stdio.h>

// .data section (initialized)
int g = 22;

#define G(n, i) (unsigned int)((unsigned long long)n >> (i*16)) & 0xffff
#define ADDRSTR "0x%04x %04x %04x %04x"

// .text section (code)
int main() 
{
    int s = 42;
    int* h = (int*) malloc(sizeof(int));

    printf("Global: " ADDRSTR "\n", G(&g, 3), G(&g, 2), G(&g, 1), G(&g, 0));
    printf("Stack:  " ADDRSTR "\n", G(&s, 3), G(&s, 2), G(&s, 1), G(&s, 0));
    printf("Heap:   " ADDRSTR "\n", G(h, 3), G(h, 2), G(h, 1), G(h, 0));

    return 0;
}

