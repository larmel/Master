volatile static int i;

int main()
{
    register int b = 0;
    do {
        b++;
    } while (i++ < 0x1234567);
    return 0;
}
