#include <cs50.h>
#include <math.h>
#include <stdio.h>

// we got quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).

int main(void) {
    float dollars;

    do {
        dollars = get_float("Change owed: ");
    } while (dollars < 0);

    int cents = round(dollars * 100);
    int quarters = cents / 25;
    cents %= 25;
    int dimes = cents / 10;
    cents %= 10;
    int nickels = cents / 5;
    int pennies = cents % 5;

    printf("%i\n", quarters + dimes + nickels + pennies);
}