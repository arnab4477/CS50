#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])

{
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]))
        {
            printf("Key must contain only alphabets");
            return 1;
        }
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 letters");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key should not contain duplicate letters");
                return 1;
            }
        }
    }

    string plaintext = get_string("Enter plaintext: ");
    printf("ciphertext: ");
    int n;
    char key;

    for (int j = 0; j < strlen(plaintext); j++)
    {

        if (isupper(plaintext[j]))

        {
            n = plaintext[j] - 65;
            key = toupper(argv[1][n]);
            printf("%c", key);
        }

        else if (islower(plaintext[j]))
        {
            n = plaintext[j] - 97;
            key = tolower(argv[1][n]);
            printf("%c", key);
        }

        else
        {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");
}