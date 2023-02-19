#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0) // If name voted for is in candidate list
        {
            candidates[i].votes++; //Increase that specific candidates votes
            return true;
        }
    }
    return false;
    /* if true wasnt activated, it means that name given was not in
    the candidate list. Only when true isnt activated will false be returned. */

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winning_vote = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= winning_vote) //Find highest vote amount candidates
        {
            winning_vote = candidates[i].votes; //Set current winning_vote to amount of votes candidate has
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winning_vote) //Check whether more than 1 candidate has the number of winning votes
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}