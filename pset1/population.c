#include <cs50.h>
#include <stdio.h>

int main(void) {
    int start_size = 0;
    int end_size = 0;
    
    do {
        start_size = get_int("Start size: ");
    } while (start_size < 9);
    
    do {
        end_size = get_int("End size: ");
    } while (end_size < start_size);
    
    int population = start_size;
    int years = 0;
    int born = 0;
    int dead = 0;

    while (population < end_size) {
        born = population / 3;
        dead = population / 4;
        population = population + born - dead;
        years++;
    }

    printf("Years: %i", years);
}
