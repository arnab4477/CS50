#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long cardN = get_long("Enter your Credit Card number: ");
    long cardN2 = cardN; // This will be used to in a different loop as the alternative for cardN
    long lengthN, firstN, first2N, a, b, c;
    long lastN, secondlastN, everyotherN, multiplyN, digitSum, validity;
    long sum1 = 0;
    long sum2 = 0;

    lengthN = log10(cardN) + 1; // This is the length of the card number
    a = pow(10, (lengthN - 1)); // This will help to get the first digit of the number
    b = pow(10, (lengthN - 2)); // This will help to get the first two digits of the number
    firstN = cardN / a;         // This is the first digit of the number
    first2N = cardN / b;        // This is the first 2 digits of the number

    while (cardN > 0)
    {                             // This loop adds every ither number starting from the second last number,
        secondlastN = cardN / 10; // multiplies them with 2, adds all the individual digits and stores the value in the variable 'sum1'
        everyotherN = secondlastN % 10;
        cardN = cardN / 100;
        multiplyN = everyotherN * 2;
        digitSum = (multiplyN / 10) + (multiplyN % 10);
        sum1 = sum1 + digitSum;
    }

    while (cardN2 > 0)
    { // This loop adds the rest of the numbers and stores the value in the variable 'sum2'
        c = cardN2 % 10;
        cardN2 = cardN2 / 100;
        sum2 = sum2 + c;
    }

    validity = (sum1 + sum2) % 10; // This validates Luhn's algorithm. If the remainder is 0, then the card is valid, else it is invalid

    if (validity == 0 && (first2N == 34 || first2N == 37) && lengthN == 15) // This will validate an American Express card

    {
        printf("AMEX\n");
    }

    else if (validity == 0 && (first2N == 51 || first2N == 52 || first2N == 53 || first2N == 54 || first2N == 55) && lengthN == 16) // // This will validate a Mastercard

    {
        printf("MASTERCARD\n");
    }

    else if (validity == 0 && (lengthN == 13 || lengthN == 16) && firstN == 4) // This will validate a Visa card

    {
        printf("VISA\n");
    }

    else

    {
        printf("INVALID\n");
    }
}