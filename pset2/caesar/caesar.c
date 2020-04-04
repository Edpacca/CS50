// Program which executes Caesar's algorithm on the letters of a user's input
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Main takes a number of arguments and produces an array of strings from them
int main(int argc, string argv[])
{
    // Returns an error if wrong number of arguments inputted
    if (argc != 2)
    {
        printf("Usage: ./ceasar key\n");
        return 1;
    }
    // If exactly 1 argument additional to ''./caesar;' is inputted then program runs
    else
    {
        // Checks each character of the second argument, i.e. second string in array
        // if character is not digit, terminates program and returns error
        int x = 0;
        while ((argv[1][x]) != '\0')
        {
            if (isdigit(argv[1][x]))
            {
                x++;
            }
            else
            {
                printf("Usage: ./ceasar key\n");
                return 1;
            }
        }

        // Converts argv string of digits to integer value, which initialises 'key'
        // Prompts for users string input
        int key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");

        // Evaluates characters from users string input
        // If alpha char, increases ascii value by the key
        // Preserves case and handles large key values
        // If not a letter then prints the character unchanged

        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            if (islower(plaintext[i]))
            {
                printf("%c", ((plaintext[i] + key - 97) % 26) + 97);
            }
            else if (isupper(plaintext[i]))
            {
                printf("%c", ((plaintext[i] + key - 65) % 26) + 65);
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }

        // Adds new line and returns 0
        printf("\n");
        return 0;
    }
}