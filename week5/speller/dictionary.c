// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
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
const unsigned int N = 65536; //512 and 1024 almost the same as 2048
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int location = hash(word);
    node *tmp = table[location];
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        tmp = tmp->next;

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    /* djb2 by Dan Bernstring - adapted to be case insensitive */
    unsigned long hash = 5381;
    int c;
    // convert chars to lowercase, first word is dereferenced, then converted to lowercase and then assigned to c. only after assignment to c is word incremented(increases address by one bit) and because its an an array of chars incrementing by one bit just goes to the next element in the array e.g the next char.
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N; // keep result within bounds of our table

    /*
    // TODO: Improve this hash function
    int ascii_sum = 0;

    for (int i = 0; i < strlen(word); i+
        if (isalpha(word[i]) != 0)
        {
            ascii_sum += toupper(word[i]);
        }
    }

    return (ascii_sum % N);

    //return toupper(word[0]) - 'A';  //#Basic option using first char.
    */
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file in reading mode, dictionary is already a pointer so no need to use &dictionary.
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {

        char buffer[LENGTH]; // Create a buffer to put each word of the dictionary in.

        while (fscanf(file, "%s", buffer) != EOF) // Reads file line by line and places each line in the buffer.
        {
            unsigned int bucket_location = hash(buffer); // Recieve the specific words
            node *new_word = malloc(sizeof(node)); // Create new node to contain the current dictionary word
            new_word->next = NULL; // When initialized point new node to NULL so that no garbage values are used.
            if (new_word == NULL)
            {
                return false;
            }
            // Copies the string from the buffer into the new nodes word member. No need to check size of word because CS50 stated that dictionaries will not have words longer than LENGTH.
            strcpy(new_word->word, buffer);
            if (table[bucket_location] != NULL) // If the element at the location the hash function provided isnt empty
            {
                node *previous = table[bucket_location]; // Saving the original node.
                // Making the new node point to the original node in order to prepend the new word. Could also be written as new_word->next = table[bucket_location]
                new_word->next = previous;
            }
            // If location was empty then simply inserts the node in the location. Earlier if statement makes sure to take care of keeping previous nodes.
            table[bucket_location] = new_word;
            word_count++;

        }
        fclose(file);
        return true;
    }

    printf("Unable to open file, NULL recieved"); //Will only reach this line if failed to load.
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            node *next = tmp->next;
            free(tmp);
            tmp = next;
        }

    }

    return true;
}
