#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("What is your name ?"); // Gets input from the user
    printf("Hello %s", answer); //Says hello to the user!
}