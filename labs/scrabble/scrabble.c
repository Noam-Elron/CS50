#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char alp[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int compute_score(string word);
int getwinner(int p1, int p2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    int winner = getwinner(score1, score2);
    if (winner == 0)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player %i wins!\n", winner);
    }
}

int compute_score(string word)
{
    int points = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (tolower(word[i]) == alp[j])
            {
                points += POINTS[j];
            }
        }
    }
    return points;
}

int getwinner(int p1, int p2)
{
    if (p1 > p2)
    {
        return 1;
    }
    else if (p2 > p1)
    {
        return 2;
    }
    return 0;
}