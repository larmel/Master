
// cc align.s; perf stat -e cycles:u,r0120:u,r01a8:u ./a.out
// cc align.c -S; cc align.s; objdump -S a.out; perf stat -e cycles:u,r0120:u,r01a8:u ./a.out

#define B27 a = b, a = b, a = b, a = b, a = b, a = b, a = b, a = b, a = b

int loop()
{
    register int i = 0, a = 1, b = 1;
    while (i++ < 0x12345678)
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
    return i;
}


/*
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }
        if (a != b)
        {
            a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b; a = b;
        }*/



int main()
{
    loop();
    /*register int i = 0, a = 1, b = 1, c = 42;
    c += b;

    while (1)
    {
        a++;
        b++;
        if (a == b)
        {
            a++, b++;
            c -= 42;
            c++;
        }

        if (a == b)
            a++, b++;

        // Size of dead code does not matter
        if (a != b)
        {
            c++;
            c++;
        }

        if (i != -1)
        {
            i++;
            c += 42;
            a += c;
            b += c;
        }
        if (i == 0x12345678)
            break;
    }*/

    //printf("c = %d\n", c);

    return 0;
}

