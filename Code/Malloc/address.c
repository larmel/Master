#include <stdlib.h>
#include <stdio.h>

/** Try different malloc implementations and check what addresses are returned
 */
#define PRINT(v) printf(#v "\t : %p\n", v);
#define TEST(n) { \
		float *a = malloc(n * sizeof(float)); \
		float *b = malloc(n * sizeof(float)); \
		printf(" %-10s : (%p, %p)\n", #n, a, b); \
		free(a), free(b); \
	}

int main(void)
{
	TEST(0x01);
	TEST(0x10);
	TEST(0x20);
	TEST(0xf0);
	TEST(0x100);
	TEST(0x123);
	TEST(0xf00);
	TEST(0xfed);
	TEST(0xfff);
	TEST(0x1000);
	TEST(0x1234);
	TEST(0xf000);
	TEST(0xfedc);
	TEST(0xffff);
	TEST(0x10000);
	TEST(0x12345);
	TEST(0xf0000);
	TEST(0xfedcb);
	TEST(0xfffff);
	TEST(0x100000);
	TEST(0x123456);
	TEST(0xf00000);
	TEST(0xfedcba);
	TEST(0xffffff);

	return 0;
}
