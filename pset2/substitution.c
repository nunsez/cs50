#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_crypted_symb(int, string);
int get_letter_index(int);
int is_cipher(string);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    string cipher = argv[1];

    if (!is_cipher(cipher)) {
        printf("Key must contain 26 unique characters.\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    int len = strlen(text);
    int crypted;

    printf("ciphertext: ");

    for (int i = 0; i < len; i++) {
        crypted = get_crypted_symb(text[i], cipher);
        printf("%c", crypted);
    }

    printf("\n");
}

int get_letter_index(int letter) {
    int is_upper = isupper(letter) ? 1 : 0;
    return is_upper ? letter - 'A' : letter - 'a';
}

int is_cipher(string input) {
    int len = strlen(input);

    if (len != 26) return 0;
    
    int abc[26] = {0};
    int index;

    for (int i = 0; i < len; i++) {
        if (!isalpha(input[i])) return 0;

        index = get_letter_index(input[i]);
        
        if (abc[index]) return 0;

        abc[index]++;
    }

    return 1;
}

int get_crypted_symb(int symb, string cipher) {
    if (!isalpha(symb)) return symb;

    int index = get_letter_index(symb);

    return isupper(symb) ? toupper(cipher[index]) : tolower(cipher[index]);
}
