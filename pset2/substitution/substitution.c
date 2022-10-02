#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



string encrypt(string plaintext, int argc, string argv[]);
int check_d(string cipher, int argc, string argv[]);
int check_a(string cipher, int argc, string argv[]);

int main(int argc, string argv[])
{
    if (argc > 2 || argc < 2)       //if user tries more than 1 argument
    {
        printf("Usage: ./substitution key\n");  //remember the user how to use the command
        return 1;
    }

    string cipher = argv[1];        //argv[1] must have 26 characters
    if (strlen(cipher) < 26 || strlen(cipher) > 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    int checkalpha = check_a(cipher, argc, argv);   //check if argv[1] is a letter
    int checkdupe = check_d(cipher, argc, argv);    //check if there arent any suplicate letters in argv[1]
    if (checkdupe != 0 || checkalpha != 0)
    {
        return 1;
    }

    string plaintext1 = get_string("plaintext:  ");     //prompt user plaintext to be encrypted
    string ciphertext = encrypt(plaintext1, argc, argv);    //encrypt plaintext

    printf("ciphertext: %s\n", ciphertext);         //print encrypted text
}


string encrypt(string plaintext, int argc, string argv[])   //encrypt plaintext
{
    string cipher = argv[1];
    int len = strlen(plaintext);
    for (int i = 0, n = 0; i < len; i++)
    {
        if (islower(plaintext[i]))      //force cipher to lowercase if plaintext is lowercase
        {
            n = 0;
            n = (int) plaintext[i] - 97;
            plaintext[i] = tolower(cipher[n]);
        }

        if (isupper(plaintext[i]))      //for cipher to uppercase if plaintext is uppercase
        {
            n = 0;
            n = (int) plaintext[i] - 65;
            plaintext[i] = toupper(cipher[n]);
        }
    }
    return plaintext;
}

int check_d(string cipher, int argc, string argv[])     //check for duplicate letters in argv[1]
{
    cipher = argv[1];
    int checkdupe = 0;
    int len = strlen(cipher);

    for (int i = 0; i < len; i++)
    {
        for (int k = i + 1; k < len; k++)
        {
            if (tolower(cipher[i]) == tolower(cipher[k]))
            {
                checkdupe++;
            }
        }
    }
    return checkdupe;
}
int check_a(string cipher, int argc, string argv[])     //check if every char of the argv[1] is a letter
{
    cipher = argv[1];
    int checkalpha = 0;
    int len = strlen(cipher);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(cipher[i]) == 0)
        {
            checkalpha++;
        }
    }
    return checkalpha;
}