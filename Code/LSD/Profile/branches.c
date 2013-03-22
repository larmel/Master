volatile int i;

int main()
{
    i = 1;
    register int n = 0;
    do {
    } while (n++ < 0x1234567);
    return 0;
}
