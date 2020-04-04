#include <stdio.h>
#include <cs50.h>

// american express 15 digits starts with 34 || 37
// Mastercard 16 digits starts 51-55

long get_credit(string prompt);


int main(void)
{
    // Request credit card number > 0
    long credit = get_credit("Credit card number: ");

    // Declare new int (numdigits) to keep original credit number stored
    long numdigits = credit;
    
    // Determine number of digits
    int count = 0;
    while (numdigits != 0)
    {
        count++;
        numdigits /= 10;
    }
        
    // Declare variable and limit to use within for loop
    // Declare int array to store every other digit with limit = num digits / 2
    long x = 10;
    int hfcount = count / 2;
    int digit_array[hfcount];

    // Iterates through credit number and stores digits in array
    for (int i = 0; i < hfcount; i++)
    {
        int digit = (((credit % (10 * x)) - (credit % x)) / x);
        digit_array[i] = digit;
        x *= 100;
    }
    
    // Declare ints for sumation calculations
    int sum1 = 0;
    int sum2 = 0;
    
    // For if takes all values < 5, doubles, then adds to sum1
    // For else takes all values > 5, *2 then -10, +1 then adds to sum2
    // This gets the digits, rather than sum, from the doubled values from the array
    for (int i = 0; i < hfcount; i++)
    {
        if (digit_array[i] < 5)
        {
            sum1 = sum1 + 2 * digit_array[i];                    
        }
        else
        {
            sum2 = sum2 + 1 + ((2 * digit_array[i]) - 10);    
        }
    }
    // Repeats a similar for loop to obtain array of other alternating digits
    // This time limit is hfcount +1
    // Bad code :( working on custom function
    long y = 1;
    int digit_array2[hfcount + 1];
    
    for (int i = 0; i <= hfcount; i++)
    {
        int digit2 = (((credit % (10 * y)) - (credit % y)) / y);
        digit_array2[i] = digit2;
        y *= 100;
    }
    
    // Sums up values from second array
    int sum3 = 0;    
    for (int i = 0; i <= hfcount; i++)
    {
        sum3 = sum3 + digit_array2[i];                    
    }
    
    // Determines final result of Luhn's Algorithm
    int sum4 = sum3 + sum2 + sum1;
    
    // Determines first two digits of credit number
    long firstdigits = credit;
    while (firstdigits > 99)
    {
        firstdigits /= 10;
    }

    // If remainder is TRUE i.e. < 0, then print INVALD
    if (sum4 % 10)
    {
        printf("INVALID\n");
    }
    // Else perform checks for provider
    else if (count == 15 && ((firstdigits == 34) || (firstdigits == 37)))
    {
        printf("AMEX\n");

    }
    else if (count == 16 && firstdigits < 56 && firstdigits > 50)
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 13 || count == 16) && ((firstdigits / 10) == 4))
    {
        printf("VISA\n");
    }
    // If Luhn's Alg is satisfied but none of the providers are, then print invalid
    else
    {
        printf("INVALID\n");
    }
}

// Function for obtaining credit card number > 0
long get_credit(string prompt)
{
    long n;
    do
    {
        n = get_long("%s", prompt);
    }
    while (n < 0);
    return n;
}
