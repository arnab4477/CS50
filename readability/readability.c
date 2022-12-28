#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_words(char *text);
int count_sentences(char *text);
int count_letters(char *text);

int main(void)

{
    string text = get_string("Enter text: ");

    float wordN, letterN, sentenceN, letterAverage, sentenceAverage, grade;

    wordN = count_words(text);
    letterN = count_letters(text);
    sentenceN = count_sentences(text);
    letterAverage = (letterN / wordN) * 100;
    sentenceAverage = (sentenceN / wordN) * 100;
    grade = round((0.0588 * letterAverage) - (0.296 * sentenceAverage) - 15.8);

    printf("%f, %f, %f, %f, %f, %f", wordN, letterN, sentenceN, letterAverage, sentenceAverage, grade);
    if ((grade < 1) || (grade == 1))
    {
        printf("Before Grade 1\n");
    }

    else if ((grade > 16) || (grade == 16))
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %.0f\n", grade);
    }
}

int count_words(char *text)
{

    float w = 0;
    float words;

    for (int i = 0; i < strlen(text); i++)
    {

        if (text[i] == ' ')

        {
            w++;
        }
    }
    words = w + 1;
    return words;
}

int count_sentences(char *text)

{

    float punctuations = 0;

    for (int i = 0; i < strlen(text); i++)
    {

        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))

        {
            punctuations++;
        }
    }

    return punctuations;
}

int count_letters(char *text)

{

    float symbols = 0;
    float letters;

    for (int i = 0; i < strlen(text); i++)
    {

        if ((text[i] == ',') || (text[i] == ')') || (text[i] == '(') || (text[i] == ';') || (text[i] == ':')
            || (text[i] == '\'') || (text[i] == '\"') || (text[i] == '.') || (text[i] == ' ') || (text[i] == '!') || (text[i] == '?')
            || (text[i] == '-'))

        {
            symbols++;
        }

        letters = strlen(text) - symbols;
    }

    return letters;
}