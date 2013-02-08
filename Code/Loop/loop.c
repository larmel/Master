
/**
 * Copy of microkernel from the paper
 * "Producing Wrong Data Without Doing Anything Obviously Wrong!"
 * 
 * Interesting counters
 * cycles:u,r0107:u,r003c:u,r013c:u,r025c:u,r01a2:u,r02a3:u
 *
 */

static int i = 0, j = 0, k = 0, l = 0;

int main() {
	int g = 0, inc = 1;
	for (; g < 65536; g++) { // 65536
		i += inc;
		i += inc;
		//j += inc;
		//k += inc;
		//l += inc;
	}
	return 0;
}
