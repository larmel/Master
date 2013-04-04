#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 0x20000 //0x7ffa // 65536 = 0x10000
#define ALIAS(a, b) (((long)a & 0xfff) == ((long)b & 0xfff))

static int inc = 0;


/**
 * Do some heavy work on long arrays
 */
void *foo(void *argument)
{
    int i;
    char *fill = malloc(0x1*sizeof(char)); // This does not need to be large ..
    char *a = malloc(0x10000*sizeof(char));
    
    char *b = malloc(0x8f000*sizeof(char));
    //if (ALIAS(a, b))
    {
        printf("foo : (%p, %p, %p) %d %d\n", fill, a, b, a - b, ALIAS(a, b));
        //printf("foo : (%p)\n", fill);
    }

    /*for (i = 0; i < N-1; ++i)
    {
        b[i] += inc;
        b[i]++;
        b[i]++;
        b[i]++;
        a[i]++;
    }*/

    return NULL;
}

/**
 * Allocate some stuff, but not much work. If bar is run before foo, then
 * internal malloc boundary will force foo to allocate with memset?
 * Does not work.. mmap is used anyway.
 */
void *bar(void* argument)
{
    char *a = malloc(10*sizeof(char));
    char *b = malloc((10*N)*sizeof(char));

    printf("bar : (%p, %p)\n", a, b);
    /*float* b = malloc(sizeof(float));
    printf("b             :  %p\n", b);
    float* c = malloc(sizeof(float));
    printf("c             :  %p\n", c);*/

    return NULL;
}

int main(void)
{
    pthread_t thread[2];
    int args[] = {0, 10000};
    char *a, *b;

    pthread_create(&thread[1], NULL, bar, &args[1]);
    pthread_create(&thread[0], NULL, foo, &args[0]);

    // Main thread uses the low-address heap segment, after bss using brk.
    a = malloc(0x1*sizeof(char));
    b = malloc(0x200000*sizeof(char));
    printf("main: (%p, %p)\n", a, b);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
 
    return 0;
}

