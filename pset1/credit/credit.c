#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int len, y, yy, h, k, kk, sum1 = 0, sum2 = 0, checksum = 0;
    char nstr[16];
    long x, xx, cnum;

    cnum = get_long("Credit card number: "); //get card number
    len = sprintf(nstr, "%ld", cnum); //number of chars
    for (y = 1; y < len; y += 2)
    {
        x = cnum / pow(10, y);   //Multiply every other digit by 2,
        k = (x % 10) * 2;   //starting with the number’s second-to-last digit
        h = k % 10 + (k / 10) % 10; //If k has 2 digits, sum them
        sum1 += h;
    }
    for (yy = 0; yy < len; yy += 2)
    {
        xx = cnum / pow(10, yy);   //sum of the digits that weren’t multiplied by 2
        kk = (xx % 10);
        sum2 += kk;
    }
    int start_cnum = cnum / pow(10, len - 2);   //card number first two digits
    if (((sum1 + sum2) % 10) == 0)
    {
        checksum = 1;
    }
    if (len == 16 && 50 < start_cnum && start_cnum < 56 && checksum == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (len == 15 && checksum == 1 && (start_cnum == 34 || start_cnum == 37))
    {
        printf("AMEX\n");
    }
    else if (len < 17 && len > 12 && checksum == 1 && start_cnum >= 40 && start_cnum <= 49)
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}