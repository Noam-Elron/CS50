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
bool isnt_cycle(int node, int next);

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

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j != i)
                printf("Prefrences[%i][%i] %i\n", i, j, preferences[i][j]);
        }
    }
    printf("\n");

    add_pairs();

    printf("Pair_Count: %i\n", pair_count);
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pairs: Winner: %i Loser: %i\n", pairs[i].winner, pairs[i].loser);
    }
    printf("\n");

    sort_pairs();

    for (int i = 0; i < pair_count; i++)
    {
        printf("Sorted Pairs: Winner: %i Loser: %i\n", pairs[i].winner, pairs[i].loser);
    }
    printf("\n");

    lock_pairs();



    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0) // If name voted in candidate list
        {
            ranks[rank] = i; // Put a "pointer" to the specific candidate in the position he ranked him
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1; // ranks[i] or j point to a specific candidate, so basicaly like saying prefrences["Bob"]["Celeste"], a voter prefers Bob over Celeste
            //Preferences positions are the same as candidates positions in their own array.
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //printf("Prefrences[%i][%i] %i\n", i, j, preferences[i][j]);
            //printf("Prefrences[%i][%i] %i\n", j, i, preferences[j][i]);
            if (preferences[i][j] > preferences[j][i])
            {

                //printf("preferences[i][j] > preferences[j][i]\n");
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{



    for (int i = 0; i < pair_count; i++)
    {
        int biggest_value = 0;
        int biggest_index = i;
        for (int j = i; j < pair_count; j++)
        {
            if ((preferences[pairs[j].winner][pairs[j].loser]) >= biggest_value)
            {
                //printf("preferences[%i][%i] == %i >= %i\n", pairs[j].winner, pairs[j].loser, preferences[pairs[j].winner][pairs[j].loser], biggest_value);
                biggest_value = preferences[pairs[j].winner][pairs[j].loser];
                biggest_index = j;
            }
        }
        pair tmp = pairs[i];
        pairs[i] = pairs[biggest_index];
        pairs[biggest_index] = tmp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if(isnt_cycle(pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            printf("[%i][%i] is locked\n", pairs[i].winner, pairs[i].loser);
        }
    }
    return;
}


// Print the winner of the election

void print_winner(void)
{
    bool not_source[candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        not_source[i] = false;
        //printf("Pre Not_Source[%i]: %d\n", i, not_source[i]);
    }



    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //printf("Locked Pairs: pairs[%i][%i] == %d\n", j, i, locked[j][i]);
            if (locked[j][i] == true)
            {
                //printf("%i isnt source\n", i);
                not_source[i] = true;
            }

        }
    }


    //printf("\n");
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("Not_Source[%i]: %d\n", i, not_source[i]);
        if (not_source[i] == false)
        {

            //printf("Source/Winner : %s\n", candidates[i]);
            printf("%s\n", candidates[i]);
        }
    }


    return;
}

bool isnt_cycle(int node, int next)
{
    if (node == next)
    {
        return false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[next][i])
            if (isnt_cycle(node, i) == false)
            {
                return false;
            }
    }
    return true;
}

