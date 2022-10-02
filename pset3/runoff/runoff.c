#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0, n = candidate_count; i < n; i++)
        if (strcmp(candidates[i].name, name) == 0)  //compare voters choices with candidates[].name (argv names)
        {
            preferences[voter][rank] = i;   //if they are the same, register their preference
            return true;    //if valid vote, return true
        }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0, n = voter_count; i < n; i++)
        for (int j = 0, h = candidate_count; j < h; j++)
            if (!candidates[preferences[i][j]].eliminated)  //iterate through vote preferences to check for eliminated candidates
            {
                candidates[preferences[i][j]].votes++;  //if not eliminated add a vote to candidates[].votes according to their preference
                break;  //break loop to add vote to the top most preference only
            }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int i = 0, n = candidate_count, h = voter_count; i < n; i++)
        if (candidates[i].votes > h / 2)    //declare winner if he has more than half of the votes
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min_vo;
    for (int i = 0, n = candidate_count; i < n; i++)
        if (!candidates[i].eliminated && candidates[i].votes < min_vo)  //use min_vo to store lowest ammount of votes from a candidate
        {
            min_vo = candidates[i].votes;
        }
    return min_vo;  //return value of lowest ammount of votes
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int check_tie = 0;
    for (int i = 0, n = candidate_count; i < n; i++)
        for (int j = i; j < n; j++)
        {
            if (!candidates[j].eliminated)
            {
                check_tie += candidates[i].votes - candidates[j].votes; //if candidates have the same ammount of votes check_tie value will be 0
            }
            else
            {
                break;
            }
        }

    if (check_tie == 0)
    {
        return true;    //return true if tied
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0, n = candidate_count; i < n; i++)
        if (candidates[i].votes <= min)
        {
            candidates[i].eliminated = true;    //eliminate candidates if their votes are equal or below min (calculated in find_min function)
        }
    return;
}