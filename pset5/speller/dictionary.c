// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 1;
unsigned int words_in_dict = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    unsigned int hash_code = hash(word);
    node *cursor = table[hash_code];

    while (cursor != NULL) {
        if (strcasecmp(cursor->word, word) == 0) {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word) {
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++))) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    char word[LENGTH + 1];
    unsigned int hash_code;
    node *n = NULL;
    FILE *dic = fopen(dictionary, "r");

    if (dic == NULL) {
        return false;
    }

    while (fscanf(dic, "%s", word) != EOF) {
        n = malloc(sizeof(node));

        if (n == NULL) {
            continue;
        }

        hash_code = hash(word);
        strcpy(n->word, word);
        n->next = table[hash_code];
        table[hash_code] = n;
        words_in_dict++;
    }

    fclose(dic);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    return words_in_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    node *cursor;
    node *tmp;

    for (int i = 0; i < N; i++) {
        cursor = table[i];

        while (cursor) {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        if (i == N - 1 && cursor == NULL) {
            return true;
        }
    }

    return false;
}
