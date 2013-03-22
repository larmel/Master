#define B22 b += i*i*a + 1

// To avoid optimization messing up too much
volatile int i = 42;

/** The trick is to pass CHUNK with an increasing value, until the
 *  LSD stops working. Compile with -O3 and -falign-loops=32.
 */
int loop(int a)
{
    register int b = i == 42 ? 1 : 0;
    do {
    #if N > 1
        if (!i) B22;
    #endif
    #if N > 2
        if (!i) B22;
    #endif
    #if N > 3
        if (!i) B22;
    #endif
    #if N > 4
        if (!i) B22;
    #endif
    #if N > 5
        if (!i) B22;
    #endif
    #if N > 6
        if (!i) B22;
    #endif
    #if N > 7
        if (!i) B22;
    #endif
    #if N > 8
        if (!i) B22;
    #endif
    #if N > 9
        if (!i) B22;
    #endif
    #if N > 10
        if (!i) B22;
    #endif
    #if N > 11
        if (!i) B22;
    #endif
    #if N > 12
        if (!i) B22;
    #endif
        // 27 bytes for increment and test
    } while (i++ < 0x1234567);
    return b;
}

int main()
{
    i = loop(10);
    return 0;
}
