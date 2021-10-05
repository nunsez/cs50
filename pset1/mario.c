#include <cs50.h>
#include <stdio.h>

void print_floor(int, int);

int main(void) {
    int height;
    int start_pad_count;

    do {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    for (int level = 1; level <= height; level++) {
        start_pad_count = height - level;
        print_floor(start_pad_count, level);
    }
}

void print_floor(int start_pad_count, int sharp_count) {
    for (int i = 0; i < start_pad_count; i++) printf(" ");
    for (int i = 0; i < sharp_count; i++) printf("#");
    printf("  ");
    for (int i = 0; i < sharp_count; i++) printf("#");
    printf("\n");
}
