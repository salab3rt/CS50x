#include <cs50.h>
#include <stdio.h>

int main(void){
    int height;

    do{
        height = get_int("whats the pyramid height? ");
    }
    while (height >= 9 || height < 1);

    for (int i=0; i<=height; i++){
        printf("%.*s", height-i, "                         ");
        printf("%.*s", i, "##################################");
        printf("  ");
        printf("%.*s", i, "##################################");
        printf("\n");
    }
}