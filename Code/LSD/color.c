#include <stdio.h>
volatile static int color;

int main()
{
    //printf("Offseting loop a bit");
    for (int i = 0; i < 1000000; ++i) {
        if (color == 0x000)
            color = 0xaaa;
        else if (color == 0xaaa)
            color = 0xfff;
        else if (color == 0xfff)
            color = 0x000;
    }
    return 0;
}
