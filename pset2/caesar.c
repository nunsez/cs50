#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_crypted_symb(int, int);
int is_number(string);

int main(int argc, string argv[]) {
    if (argc != 2 || !is_number(argv[1])) {
        printf("Usage: %s key\n", argv[0]);

        return 1;
    }

    string text = get_string("plaintext: ");
    int len = strlen(text);
    int key = atoi(argv[1]);
    int crypted;

    printf("ciphertext: ");

    for (int i = 0; i < len; i++) {
        crypted = get_crypted_symb(text[i], key);
        printf("%c", crypted);
    }

    printf("\n");
}

int is_number(string input) {
    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        if (!isdigit(input[i])) return 0;
    }

    return 1;
}

int get_crypted_symb(int symb, int key) {
    if (!isalpha(symb)) return symb;

    int first = isupper(symb) ? 'A' : 'a';

    return first + (symb - first + key) % 26;
}
