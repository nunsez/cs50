#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool is_end_of_sentence(int);
void print_grade(int);

int main(void) {
    string s = get_string("Text: ");
    int len = strlen(s);
    int letters = 0;
    int words = 0;
    int sentences = 0;
    bool inside_word = false;
    int chr;

    for (int i = 0; i < len; i++) {
        chr = s[i];

        if (isalpha(chr)) {
            if (!inside_word) inside_word = true;
            letters++;
        }

        if ((inside_word && chr == ' ') || is_end_of_sentence(chr)) {
            inside_word = false;
            words++;
        }

        if (is_end_of_sentence(chr)) sentences++;
    }

    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    print_grade(grade);
}

bool is_end_of_sentence(int chr) {
    return chr == '.' || chr == '!' || chr == '?';
}

void print_grade(int grade) {
    if (grade >= 16) {
        printf("Grade 16+\n");
    } else if (grade < 1) {
        printf("Before Grade 1\n");
    } else {
        printf("Grade %i\n", grade);
    }
}
