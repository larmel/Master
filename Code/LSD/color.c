#include <stdio.h>
volatile static int color;

int main()
{
    printf("Fixing colors");
    for (int i = 0; i < 10000000; ++i) {
        if (color == 0x000)
            color = 0xaaa;
        else if (color == 0xaaa)
            color = 0xfff;
        else if (color == 0xfff)
            color = 0x000;
    }
    return 0;
}
