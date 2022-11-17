// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// original - 26
const unsigned int N = 1170;

// Hash table
node *table[N];

// for use in load and SIZE function
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash word to obtain hash value
    int hash_code = hash(word);

    // access linked list at the index in the hash table

    // traverse linked list, looking for the word (strcasecmp)
    node *cursor = table[hash_code];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else if (cursor == NULL)
        {
            return false;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_code = 0;
    // TODO: Improve this hash function

    // loop through word to find hash code
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        // test for apostrophes
        if (word[i] == '\'')
        {
            hash_code += toupper(word[i]);
        }
        // else sum up all ascii values in word
        else
        {
            hash_code += (toupper(word[i]) - 'A');
        }
    }

    //return toupper(word[0]) - 'A' ;
    return hash_code;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the file
    FILE *dict = fopen(dictionary, "r");

    // check if value is null
    if (dict == NULL)
    {
        printf("couldn't open file");
        return false;
    }

    // temporary character array to store word
    char word[LENGTH + 1];

    // loop through entire dictionary, reading words to memory
    while (fscanf(dict, "%s", word) != EOF)
    {
        // read word from file, copy into temporary array

        // create new node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Malloc returned NULL");
            return false;
        }
        // copy word into node

        strcpy(n->word, word);
        n->next = NULL;

        // insert node into hash table
        // use hash function
        int hash_code = hash(word);

        if (table[hash_code] == NULL)
        {
            n->next = NULL;
        }
        else
        {
            n->next = table[hash_code];
        }
        //printf("%p\n",&table[0]->next);

        table[hash_code] = n;
        //table[hash_code]->next;

        word_count++;
    }
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

void free_memory(node *n)
{
    if (n == NULL)
    {
        return;
    }
    // TODO: Free parents recursively
    else
    {
        free_memory(n->next);

        // TODO: Free child

        free(n);
    }


}
// Unloads dictionary from memory, returning true if successful, else false

bool unload(void)
{
    // TODO
    // free linked list

    for (int i = 0; i <= N; i++)
    {
        free_memory(table[i]);
    }

    return true;
}

