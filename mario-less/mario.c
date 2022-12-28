#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int N;
    do
    {
        N = get_int("Enter a number between 1 and 8\n");
    }
    while (N < 1 || N > 8);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i + j < N - 1)
            {

                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}