#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int compute_score(string text);
int main(void)

{

    string word1 = get_string("Enter word one: ");
    string word2 = get_string("Enter word two: ");

    char word1value = compute_score(word1);
    char word2value = compute_score(word2);

    if (word1value > word2value)
    {
        printf("Player 1 wins!\n");
    }

    else if (word1value < word2value)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tied\n");
    }
}

int compute_score(string text)

//Computes the score of a given word
{
    int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int letterValue;
    int valueSum = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == ',')
        {
            continue; //If it is not an alphabet then it does not add any value
        }

        else
        {
            letterValue = toupper((text[i])) - 65; //Maps the letters to the points in the array
            valueSum += POINTS[letterValue]; //Adds the points
        }
    }

    return valueSum;
}

