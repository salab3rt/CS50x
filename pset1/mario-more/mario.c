#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height; //User prompt for height


    do  //Prompt pyramid height
    {
        height = get_int("What's the pyramind height? ");
    }
    while (height >= 9 || height < 1); //Define Height limits

    for (int i = 0; i < height; i++)
    {
        for (int h = height - 1; h - i > 0 ; h--)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1 ; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i + 1 ; j++)
        {
            printf("#");
        }
        printf("\n");

    }
}