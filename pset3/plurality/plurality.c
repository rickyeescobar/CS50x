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
    // TODO
    bool status = false;
    for (int j = 0; j <= candidate_count; j++)
    {
        if (!candidates[j].name)
        {
            status = false;
            return status;
        }
        if (strcmp(name, candidates[j].name) == 0)
        {
            //printf("added a vote to %s\n", candidates[j].name);
            candidates[j].votes ++;
            status = true;
            return status;
        }
        else
        {
            status = false;
        }
    }
    return status;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int i = 0;
    for (i = 0; i < candidate_count; i++)
    {
        //printf("candidate %s has %i votes\n", candidates[i].name, candidates[i].votes);
    }

    i = 0;
    int j = 0;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            if (candidates[j].votes > candidates[i].votes)
            {
                candidates[candidate_count] = candidates[j];
                candidates[j] = candidates[i];
                candidates[i] = candidates[candidate_count];
            }
        }
    }

    printf("%s\n", candidates[candidate_count - 1].name);

    for (i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == candidates[candidate_count - 1].votes
            && strcmp(candidates[i].name, candidates[candidate_count - 1].name) != 0)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}