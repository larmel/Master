
#define S1 a ^= 1 << b;
#define S2 b += d + a - 8;
#define S3 c = -c;
#define S4 d = 2*d % 512;
#define S S1 S2 S3 S4

/**
 * When Number of instructions in loop is less than some limit, the LSD counter
 * spikes. If there are too many, the LSD_OVERFLOW counter is not 0, and LSD
 * is severely reduced. 
 * Q: What are these counters really counting?
 * Q: Is this actually valid on Ivy Bridge?
 */
int main()
{
	int a = 1, b = 2, c = 3, d = 4;
	for (int i = 0; i < 5000; ++i)
	{
		S
		S1
		S1 // Lots of cycles with LSD
		//S1 // Low LSD, but no OVERFLOW
		//S1 // Triggers LSD_OVERFLOW
	}
	return 0;
}

