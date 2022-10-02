// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 56;

//started by using a 1D array[676], total time was over 0.2 seconds in lalaland.txt
//improved total runtime to sub 0.1 sec, by using a 3D array[56][56][46]

// Hash table
node *table[N][N][LENGTH + 1];
int word_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index0 = hash(word);
    unsigned int index1 = hash(&word[1]);
    unsigned int index2 = strlen(word);

    //find word correspondence in hash table, by hashing it
    //if not found on the the first bucket, move to the next, untill NULL
    for (node *trav = table[index0][index1][index2]; trav != NULL; trav = trav->next)
    {
        //compare word in table, and word in text case insensitive
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    if (!isalpha(word[0]))
    {
        return ((int) word[0]);
    }
    if (!isalpha(word[1]))
    {
        return (toupper(word[0]) - 'A');
    }

    return ((toupper(word[0]) - 'A') + (toupper(word[1]) - 'A'));
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *dict = fopen(dictionary, "r");    //read file
    char *tmp = malloc(sizeof(char) * LENGTH + 1);  //temporary variable to hold words in dictionary
    node *new_node = NULL;

    if (dict == NULL)
    {
        return false;
    }

    while (fscanf(dict, "%s", tmp) != EOF)  //scan file for trings and store them in tmp variable
    {
        if (tmp != NULL)
        {
            new_node = malloc(LENGTH + 1 * sizeof(node));    //allocate memory for each new node
        }

        unsigned int index0 = hash(tmp);
        unsigned int index1 = hash(&tmp[1]);
        unsigned int index2 = strlen(tmp);

        strcpy(new_node->word, tmp); //copy each word to new node node

        new_node->next = table[index0][index1][index2]; //new node points at where table is pointing
        table[index0][index1][index2] = new_node;    //then point table at new node
        word_counter++; //count each word copied to table

        //printf("table[%i][%i][%i] - %s \n", index0, index1, index2, table[index0][index1][index2]->word);
    }

    fclose(dict);
    free(tmp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_counter > 0)
    {
        return word_counter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *trav = NULL;
    node *tmp = NULL;

    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            for (int j = 0; j <= LENGTH; j++)
            {
                for (trav = table[i][k][j]; trav != NULL; trav = tmp) //traverse the array using a traversal variable
                {
                    tmp = trav->next;   //hold trav->next pointer in a temporary variable
                    free(trav);         //free traversal variable, and subsequently free the position that table[i][k][j] was pointing at
                    word_counter--;     //keep track of the number of frees, by substracting the word counter
                }
            }
        }
    }

    if (word_counter == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
