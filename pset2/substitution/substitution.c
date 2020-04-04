#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Check number of arguments
    if (argc != 2)
    {
        printf("Usage: ./ceasar key\n");
        return 1;
    }

    int x = 0;
    char key[26];

    while ((argv[1][x]) != '\0')
    {
        // Checks each char, if alpha then assigns to new array called key
        if (isalpha(argv[1][x]))
        {
            key[x] = argv[1][x];
            x++;
        }
        // Error shows if char is not a letter
        else
        {
            printf("Key must only contain letters\n");
            return 1;
        }
    }

    // Check number of characters
    if (x != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check for repeated characters
    for (int i = 0; i < x; i++)
    {
        for (int j = i + 1; j < x; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters. \n");
                return 1;
            }
        }
    }


    // Initialises a char array to the ALPHABET
    int abet[26];
    int A = 65;

    for (int i = 0; i < 26; i++)
    {
        abet[i] = A;
        A++;
    }

    // Changes key from letter index to difference between corresponding alphabet letter
    // Adapts for lower and upper case
    for (int i = 0; i < 26; i++)
    {
        if (isupper(key[i]))
        {
            key[i] = (key[i] - abet[i]);
        }
        else if (islower(key[i]))
        {
            key[i] = (key[i] - (abet[i] + 32));
        }
    }

    // Gets string from user
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    // Iterates through users string
    // If char is a letter, scans through alphabet until a match is found regardless of case
    // Applies corresponding shift to that letter and moves on
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if isalpha(plaintext[i])
        {
            for (int j = 0; j < 26; j++)
            {
                if (plaintext[i] == abet[j])
                {
                    printf("%c", (plaintext[i] + key[j]));
                }
                else if (plaintext[i] == (abet[j] + 32))
                {
                    printf("%c", (plaintext[i] + key[j]));
                }
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}