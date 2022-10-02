// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];
int word_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    for (node *trav = table[hash(word)]; trav != NULL; trav = trav->next)
    {
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
    int hash_1 = 0;
    int hash_2 = 0;

    if (!isalpha(word[1]))
    {
        hash_2 = 0;
    }
    else
    {
        hash_2 = (toupper(word[1]) - 'A');
    }

    hash_1 = (toupper(word[0]) - 'A');

    //printf("%i \n", (hash_1 * 25 + hash_2));

    return (hash_1 * 26 + hash_2); //
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    //unsigned int index;
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
            new_node = malloc(sizeof(node));    //allocate memory for each new node
        }

        unsigned int index = hash(tmp);
        strcpy(new_node->word, tmp); //copy each word to new node node

        new_node->next = table[index]; //new node points at where table is pointing
        table[index] = new_node;    //then point table at new node
        word_counter++; //count each word copied to table
    }
    //free(new_node);
    fclose(dict);
    free(tmp);
    //printf("%i \n", word_counter);
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
    int free_count = 0;
    for (int i = 0; i < N; i++)
    {
        node *trav = table[i];
        while (trav != NULL)
        {
            node *tmp = trav->next;
            free(trav);
            trav = tmp;
            word_counter--;
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
