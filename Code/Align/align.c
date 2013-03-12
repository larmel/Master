
// cc align.s; perf stat -e cycles:u,r0120:u,r01a8:u ./a.out
int main()
{
	register int i = 0, a = 1, b = 1, c = 42;
	c += b;
	while (1)
	{
		a++;
		b++;
		if (a != b)
			break;

		if (b == c)
			break;

		if (i != -1)
		{
			i++;
			a++;
			b++;
			c += 42;
		}
		if (i == 0x12345678)
			break;
	}

	//printf("c = %d\n", c);

	return 0;
}

