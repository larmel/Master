/**
 * Copy of microkernel from the paper
 * "Producing Wrong Data Without Doing Anything Obviously Wrong!"
 * 
 * Interesting counters
 * cycles:u,r0107:u,r003c:u,r013c:u,r025c:u,r01a2:u,r02a3:u
 *
 */

static int i, j, k;

int main() {
	int g = 0, inc = 1;

	if ((((long)&inc) & 0xfff) == (((long)&j) & 0xfff)) 
	{
		int dummy = 0, t1 = g, t2 = inc;
		for (; t1 < 65536; t1++) {
			i += t2;
			j += t2;
			k += t2;
		}
		g = t1;
		goto skip;
	}

	for (; g < 65536; g++) {
		i += inc;
		j += inc;
		k += inc;
	}

skip:
	return 0;
}
