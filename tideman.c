#include <cs50.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// checks if there is a cylce in locked graph
bool visited [MAX];
bool stack [MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void swap (int i, int j);
bool iscyclic ();
bool iscyclic_recur (int src);

//help mehtods for testing. not used in solution
void printpairs(void);
void printgraph(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
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
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i ++) {
        if (strcmp(candidates[i], name) == 0 ) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i ++) {
        for (int j = i + 1; j < candidate_count; j ++) {
            preferences [ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i ++) {
        for (int j = 0; j < candidate_count; j ++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }

    return;
}

//Sort pairs in decreasing order by strength of victory
//selection sort
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i ++) {
        int max =  preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];;
        int max_idx = -1;
        for (int j = i + 1; j < pair_count; j ++) {
            int vote_diff = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (vote_diff > max) {
                max = vote_diff;
                max_idx = j;
            }
        }
        if (max_idx != -1) swap (i, max_idx);
    }
    //printpairs();
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i ++) {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (iscyclic()) locked[pairs[i].winner][pairs[i].loser] = false;
    }
    //printgraph();
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // create and intialize bool arr to false
    bool winner [candidate_count];
    for (int i = 0; i < candidate_count; i ++) winner[i] = true;

    for (int i = 0; i < candidate_count; i ++) {
        for (int j = 0; j < candidate_count; j ++ ) {
            if (locked[i][j]) {
                winner[j] = false;
            }
        }
    }
    for (int k = 0; k < candidate_count; k ++) {
        if (winner[k]) {
             printf ("%s\n", candidates[k]);
        }
    }
    return;
}

void swap (int i, int j) {
    pair temp;
    temp.winner = pairs[i].winner;
    temp.loser = pairs[i].loser;

    pairs[i] = pairs[j];
    pairs[j] = temp;
}

bool iscyclic () {
    //clear visited and stack arrays
    for (int i = 0; i < candidate_count; i ++) {
        visited[i] = false;
        stack[i] = false;
    }
    for (int i = 0; i < candidate_count; i ++) {
        if (visited[i]) continue;
        if (iscyclic_recur (i)) return true;
    }

    return false;
}

bool iscyclic_recur (int src) {
    if (stack[src]) return true;
    visited[src] = true;
    stack[src] = true;
    for (int i = 0; i < candidate_count; i ++) {
        if (locked[src][i] && iscyclic_recur(i)) return true;
    }
    stack[src] = false;

    return false;
}

//help method for testing. not used in solution
void printpairs (void) {
    for (int i = 0; i < pair_count; i ++) {
        printf ("%s -> %s %i vs. % i\n", candidates[pairs[i].winner], candidates[pairs[i].loser],
            preferences[pairs[i].winner][pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner] );
    }
}

// help method for testing. not used in solution
void printgraph (void) {
    for (int i = 0; i < candidate_count; i ++) {
        for (int j = 0; j < candidate_count; j ++) {
            printf("%d ", locked[i][j]);
        }

        printf ("\n");
    }
}
