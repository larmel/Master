
/**
 * Copy of microkernel from the paper
 * "Producing Wrong Data Without Doing Anything Obviously Wrong!"
 */

static int i = 0, j = 0, k = 0;

int main() {
	int g = 0, inc = 1;
	//printf("Address of stack: %p\n", &g);
	for (; g < 65536; g++) {
		i += inc;
		j += inc;
		k += inc;
	}
	return 0;
}
