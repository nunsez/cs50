#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string);

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void) {
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score1 < score2) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }
}

int compute_score(string word) {
    int length = strlen(word);
    int score = 0;
    int letter;

    for (int i = 0; i < length; i++) {
        letter = word[i];

        if (isalpha(letter)) {
            letter = tolower(letter);
            score += POINTS[letter - 'a'];
        }
    }

    return score;
}
