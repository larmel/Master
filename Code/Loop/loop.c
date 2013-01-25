
volatile long limit = 1000000;
volatile long n = 0;

main() {
	long i;
	for (i = 0; i < limit; i++) {
		if (i % 2)
			n += 1;
		else
			n -= 1;
	}
}
