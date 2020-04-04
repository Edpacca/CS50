// Program to determine the grade or "readability" of user's inputted text

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // Ask user for input
    string s = get_string("Text: ");

    // Initialise variables to count letters, words and sentences
    // Number words = number of spaces +1 therefore initialise to 1
    long lettcount = 0, wordcount = 1, stopcount = 0;

    // Iterate through string adding letters, spaces and exclamations to relevant totals
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            lettcount++;
        }
        else if (s[i] == ' ')
        {
            wordcount++;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            stopcount++;
        }
    }

    // Initialise variables as floats for equation
    // Seperate lines are cleaner here
    float L = 100 * ((float) lettcount / (wordcount));
    float S = 100 * ((float) stopcount / (wordcount));

    // Calculate the readability grade
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Prints grade between 1 - 15, 16+ or before 1
    if (index >= 1 && index < 16)
    {
        printf("Grade %.0f\n", index);
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
}