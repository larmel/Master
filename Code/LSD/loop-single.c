#include <stdio.h>
/* Standalone program to illustrate how chunk fetch limit can be hit 
 * Insert dummy statement to push alignment to fit in 12 chunks.
 * 2x speedup by keeping the call to printf
 */
#define B27 a = b, a = b, a = b, a = b, a = b, a = b, a = b, a = b, a = b

int main()
{
    register int i = 0, a = 1, b = 1;
    printf("What is going wrong?");
    while (i++ < 0x12345678)
    {
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
    return 0;
}
