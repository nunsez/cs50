#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int, string, int[]);
void record_preferences(int[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int, int);

int main(int argc, string argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++) {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
    int winner;
    int loser;
    bool condition;

    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (preferences[i][j] == preferences[j][i]) continue;

            condition = preferences[i][j] > preferences[j][i];
            loser = condition ? j : i;
            winner = condition ? i : j;

            pairs[pair_count].winner = winner;
            pairs[pair_count].loser = loser;
            pair_count++;
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
    int winner1;
    int winner2;
    int loser1;
    int loser2;
    pair pair1;

    for (int i = 0; i < pair_count; i++) {
        winner1 = pairs[i].winner;
        loser1 = pairs[i].loser;
        pair1 = pairs[i];

        for (int j = 1; j < pair_count - i; j++) {
            winner2 = pairs[j].winner;
            loser2 = pairs[j].loser;

            if (preferences[winner1][loser1] < preferences[winner2][loser2]) {
                pairs[i] = pairs[j];
                pairs[j] = pair1;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
    int winner;
    int loser;

    for (int i = 0; i < pair_count; i++) {
        winner = pairs[i].winner;
        loser = pairs[i].loser;

        if (!check_cycle(winner, loser)) locked[winner][loser] = true;
    }
}

// Print the winner of the election
void print_winner(void) {
    int rank;

    for (int i = 0; i < candidate_count; i++) {
        rank = 0;

        for (int j = 0; j < candidate_count; j++) {
            if (!locked[j][i]) rank++;
        }

        if (rank == candidate_count) printf("%s\n", candidates[i]);
    }
}

bool check_cycle(int winner, int loser) {
    if (locked[loser][winner] == true) return true;

    for (int i = 0; i < candidate_count; i++) {
        if (locked[i][winner] == true) return check_cycle(i, loser);
    }

    return false;
}
