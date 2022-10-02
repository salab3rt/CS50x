#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_phrases(string text);
int main(void)
{
    string text1 = get_string("Text: ");
    float index = 0;
    int letters = count_letters(text1);
    int words = count_words(text1);
    int phrases = count_phrases(text1);
    float l = (float) letters / (float) words * 100.0;
    float s = (float) phrases / (float) words * 100.0;
    index = 0.0588 * l - 0.296 * s - 15.8;  //Coleman-Liau index
    int grade = roundf(index);              //round index to an int

    if (index < 1)                          //if grade is below 1
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)                    //if grade is above 16
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);        //every other grade
    }
}

int count_letters(string text)              //count number of letters
{
    int letters = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))               //counter for every alphabetic char
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)                //count number of words, using spaces for reference
{
    int words = 1;                           //int words is set to one, to count the first word
    for (int i = 0, len = strlen(text); i < len ; i++)  //be fore the first space
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    if (words == 1)     //int words is set to 1, to prevent counting extra word if only one word is typed
    {
        words--;
    }
//    printf("%i \n", words);
    return words;
}

int count_phrases(string text)              //count sentences by counting . ! ?
{
    int phrases = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.')
        {
            phrases++;
        }
        if (text[i] == '!')
        {
            phrases++;
        }
        if (text[i] == '?')
        {
            phrases++;
        }
    }
//    printf("%i \n", phrases);
    return phrases;
}