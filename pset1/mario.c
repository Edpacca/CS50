// Gets user input to print out the height of a pyramid
#include <cs50.h>
#include<stdio.h>

// New function to get height within range 1 - 8
int get_height(string prompt);

int main (void)
{
    // Asks user for input
    // Declares integers and limits for printing ''#'' and ' '
    int h = get_height("Height: ");
    int spacelim = h - 1;
    int hashlim = 1;
    int space, hash;

    while (hashlim <= h)
    {
        // Prints spaces first
        for (space = 0; space < spacelim; space++)
        {
            printf(" ");
        }

        // Prints hashes
        for (hash = 0; hash < hashlim; hash++)
        {
            printf("#");
        }

        // Prints central gap
        printf("  ");

        // Prints other side of pyramid
        for (hash = 0; hash < hashlim; hash++)
        {
            printf("#");
        }

        /'//'
        printf("\n");
        ++hashlim;
        --spacelim;
    }

}


int get_height(string prompt)
{
    int h;
    do
    {
        h = get_int("%s", prompt);
    }
    while (h < 1 || h > 8);
    return h;
}
