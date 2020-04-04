// Deduce minimum number of available coins required to make up the user inputted monetary value

#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_cash(string prompt);

int main(void)
{
    float change = get_cash("Change owed: ");
    // converts float to integer
    int cents = round(change * 100);
    // calculates how many quarters in "cents" and the remainder
    int quarters = cents / 25;
    int left25 = cents % 25;

    // if remainder is 0 then prints number of quaters
    if (left25)
    {
        //if remainder != 0, determine how many dimes are in the remainder from quarters "left25"
        //iterates through 10, 5 and 1c each time the remainder is true
        int dimes = left25 / 10;
        int left10 = left25 % 10;

        if (left10)
        {
            int nickels = left10 / 5;
            int left5 = left10 % 5;

            if (left5)
            {
                int pennies = left5 / 1;
                int coins = quarters + dimes + nickels + pennies;
                printf("%i\n", coins);
            }
            // as soon as the remainder = 0, add up and print the number of coins.
            else
            {
                int coins = quarters + dimes + nickels;
                printf("%i\n", coins);
            }
        }
        else
        {
            int coins = quarters + dimes;
            printf("%i\n", coins);
        }
    }
    else
    {
        printf("%i\n", quarters);
    }

// prompt user for a postive cash float value
}
float get_cash(string prompt)
{
    float cash;
    do
    {
        cash = get_float("%s", prompt);
    }
    while (cash < 0.00);
    return cash;
}
