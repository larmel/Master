#include <stdlib.h>
#include <stdio.h>

static int a ;
static int b = 42;

int main () {
	int c = 0;
	int * d = malloc ( sizeof ( int ) ) ;
	printf ( " stack : %p heap : %p bss : %p data : %p \n" , &c , d , &a, &b);
	return 0;
}
