#include <stdio.h>
#include <stdlib.h>

static int a;      // .bss
static int b = 42; // .data

int this_is_an_external_variabjhaskfjhsakdfjhaskdfjhskfhjaskdfjhskfjhaskdfjhaskdfjhaskfjhaskdfhjaskdjfhaskfhjaskdjfhaskfhjskajdfhaskjfhaskdfhjsakdjfhskdfjhle = 1;

int main()
{
    int c = 0; // .stack
    int *d = malloc(sizeof(int)); // .heap
    printf("stack: %p\nheap: %p\nbss: %p\ndata: %p\n", &c, d, &a, &b);
    return 0;
}
