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
bool is_cycle(int head, int next);

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
    /*
    printf("\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                printf("Preferences[%i][%i] = %i\n", i, j, preferences[i][j]);
            }
        }
    }

    printf("\n");
    */
    add_pairs();
    printf("Pair Count: %i\n", pair_count);
    /*
    for (int i = 0; i < pair_count; i++)
    {
        printf("Unsorted: Pair[%i].winner = %i=%s , Pair[%i].loser = %i=%s, Votes = %i\n ", i, pairs[i].winner, candidates[pairs[i].winner], i, pairs[i].loser, candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
    }
    printf("\n");
    */
    sort_pairs();

    for (int i = 0; i < pair_count; i++)
    {
        printf("Sorted: Pair[%i].winner = %i=%s , Pair[%i].loser = %i=%s, Votes = %i\n", i, pairs[i].winner, candidates[pairs[i].winner], i, pairs[i].loser, candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
    }
    printf("\n");

    lock_pairs();


    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                printf("locked[%i][%i] = %d\n", i, j, locked[i][j]);
            }
        }
    }
    printf("\n");
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
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
            if (i != j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
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
            if (preferences[i][j] > preferences[j][i])
            {
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
        bool swap = false;
        for (int j = 0; j < pair_count-1; j++)
        {
            if (preferences[pairs[j+1].winner][pairs[j+1].loser] > preferences[pairs[j].winner][pairs[j].loser])
            {
                //printf("Switch: pairs[%i] with pairs[%i]. %i vs %i\n", j+1, j, preferences[pairs[j+1].winner][pairs[j+1].loser], preferences[pairs[j].winner][pairs[j+1].loser]);
                pair tmp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = tmp;
                swap = true;
            }
        }
        if (swap == false)
        {
            break;
        }
    }
    printf("\n");
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    locked[pairs[0].winner][pairs[0].loser] = true;

    for (int i = 1; i < pair_count; i++)
    {
        if (is_cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            printf("Locked: [%i], [%i]\n", pairs[i].winner, pairs[i].loser);
            printf("\n");
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    return;
    }
}

bool is_cycle(int head, int next)
{
    
}



// Print the winner of the election
void print_winner(void)
{
    int winner = candidate_count + 1; // can never happen

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                break;
            }
            if (j == (candidate_count-1))
            {
                winner = i;
            }
        }
        if (winner != (candidate_count + 1))
        {
            printf("%s\n", candidates[winner]);
            break;
        }
    }
    return;
}


/*
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //locked[pairs[0].winner][pairs[0].loser] = true;

    for (int i = 0; i < pair_count; i++)
    {
        if (is_cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}
*/


/*
bool is_cycle(int head, int next)
{
    if (head == next)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[next][i] == true)
        {
            if(is_cycle(head, i) == true)
            {
                return true;
            }
        }
    }
    return false;
*/


/* SCRAP FOR LOCK_PAIR's IS_CYCLE NON RECURSIVE FUNCTION
for (int g = 0; g < candidate_count; g++)
    {
        while (true)
        {
            int count = 0;
            if (head == next)
            {
                return true;
            }
            for (int h = g; h < candidate_count; h++)
            {
                if (locked[next][h] == true)
                {
                    printf("%i is pointing to %i\n", next, h);
                    count++;
                    next = h;
                    break;
                }
                else if ((g == (candidate_count-1)) && (h == (candidate_count-1)))
                {
                    return false;
                }
            }
            if (pointing == false)
            {
                break;
            }
        }
    }


*/


