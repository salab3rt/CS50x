#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("whats the pyramid height? ");
    }
    while (height >= 9 || height < 1);      //height limits

    for (int i = 0; i < height; i++)
    {
        for (int k = i; k < height - 1; k++)    //spaces prints
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)    //# prints
        {
            printf("#");
        }
        printf("\n");
    }
}