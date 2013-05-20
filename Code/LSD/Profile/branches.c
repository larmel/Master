volatile static int n;

int main()
{
    register int i = 0;
    do {
    } while (i++ < 0x1234567);
    return 0;
}
