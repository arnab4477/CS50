// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

unsigned int wordNum = 0; //this will be used to count the words in the file

#define DICTIONARY "dictionaries/large"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    unsigned int index = hash(word); //assigns an index to be put in the table array using the 'hash' fumtion
    //table[index] = head;
    node *curser = table[index];; //the curser points to the index where the word is

    //I saw on internet that the 'strcasecmp' can't be used to compare between a cinst char* and char*
    //This code below copies the word to a char* so that I can use 'strcasecmp'
    //int word_length = strlen(word);
    //char tmp_word[word_length];
//
    //for (int i = 0; i < word_length; i++)
    //{
    //    tmp_word[i] = word[i];
    //}

    while (curser != NULL)
    {
        //Checks if the word matches with the word in that linked list
        if ((strcasecmp(word, curser->word)) == 0)
        {

            return true;
        }

        //if it doesn't match then move onto the next word
        curser = curser->next;

    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO:
    unsigned int wordlength = 0, asciivalue = 0, n = 0;

    while (word[n] != '\0')
    {
        wordlength++;
        n++;
    }
    for (int i = 0; i < wordlength; i++)
    {
        asciivalue = asciivalue + toupper(word[i]);
    }

    return (asciivalue - 39) % 26;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)

// TODO
{

    char words[LENGTH + 1]; //array where the words will be stored at
    unsigned int index;
    FILE *input = fopen(dictionary, "r"); //opens the dictionary
    if (input == NULL) //checks if the file is NULL
    {
        return false;
    }

    while (fscanf(input, "%s", words) != EOF) //copies the words onto the array untill it reaches the end of the file
    {
        wordNum++; //counts the number of the words in the file
        node *tmp = malloc(sizeof(node)); //creates a node to put the word in a linked list in the array
        if (tmp == NULL) //checks if there if there is enough space for memory allocation
        {
            return false;
        }
        index = hash(words); //hashes the word
        strcpy(tmp->word, words); //copies the word into the node
        tmp->next = table[index]; //if there is a head file already then tmp points to that
        table[index] = tmp; //tmp becomes the new head file
    }



    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordNum;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++) //goes through all the buckets of the hash table
    {
        node *trav = table[i];
        while (trav) //goes though all the linked list
        {
            node *tmp = trav;
            trav = trav->next; //goes to the next list
            free(tmp);
        }

        if (trav == NULL)
        {
            return true;
        }
    }

    return false;
}
