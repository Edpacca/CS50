// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct list_node
{
    char word[LENGTH + 1];
    struct list_node *next;
}
node;

// Number of buckets in hash table
// 27^3 because we have unique index based on first 3 letters
const unsigned int N = 27 * 27 * 27;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Checks for any words not in dictionary but are spelled correctly
    if (strcasecmp(word, "I") == 0)
    {
        return true;
    }
    // gets the index from hash function
    // cursor points at first element of list at the index location
    unsigned int index;
    index = hash(word);
    node *cursor = table[index];

    // initial check for NULL speeds things up
    if (table[index] == NULL)
    {
        return false;
    }
    else
    {
        // checks if null, if not compare the words
        // if they don't match, move onto next list item
        while (cursor->next != NULL)
        {
            if (strcasecmp(word, cursor->word) == 0)
            {
                return true;
            }
            else
            {
                cursor = cursor->next;
            }
        }

        // once null is reached, check if last word matches
        // else return false
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // checks for 1 letter words and returns index location
    if (word[1] == '\0')
    {
        unsigned int index = (word[0]);
        return index;
    }
    // checks for two letter words and indexes with Ax + C linear equation (x = 26)
    else if (word[2] == '\0')
    {
        const char lc_word[2] = {tolower(word[0]), tolower(word[1])};
        unsigned int index = ((lc_word[0] - 96) * 26) + lc_word[0] + lc_word[1] - 192;
        return index;
    }
    // else indexes with quadratic eqauation Ax^2 + Bx + C
    else
    {
        const char lc_word[3] = {tolower(word[0]), tolower(word[1]), tolower(word[2])};
        unsigned int index = ((lc_word[0] - 96) * 26 * 26) + ((lc_word[1] - 96) * 26) + lc_word[0] + lc_word[1] + lc_word[2] - 288;
        return index;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dict_loaded = false;
    word_count = 0;

    // Initialise table to null
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // open dictionary and check if successful
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    else
    {
        dict_loaded = true;
    }

    // declare character array word and scan through the dictionary
    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        // for each word, increase global word count and malloc node
        word_count++;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Memory not allocated\n");
            return 1;
        }

        // copy the word into the node and hash it
        // set node pointer to null
        strcpy(n->word, word);
        unsigned int index = (hash(word));
        n->next = NULL;

        // Checks if index locaiton has a list already
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        // if there's already a list, use tmp to insert node at head
        else if (table[index] != NULL)
        {
            node *tmp = table[index];
            table[index] = n;
            n->next = tmp;
        }
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // uses global word count
    if (!dict_loaded)
    {
        return 0;
    }
    else
    {
        return word_count;
    }

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loops through table
    // for each list, free first element and move onto nest until NULL
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}