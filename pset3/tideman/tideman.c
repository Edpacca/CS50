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
            int rank = j;
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(rank, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        printf("\n");
        record_preferences(ranks);
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
    // check entered name against candidate list
    for (int k = 0; k < candidate_count; k++)
    {
        if (!strcmp(name, candidates[k]))
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // record the preferences in an array
    // starts with first rank, sets preference over all other ranks
    // for next rank, ignores the higher ranked preference
    int n = candidate_count - 1;
    for (int k = 0; k < n; k++)
    {
        for (int l = 0; l < (n - k) ; l++)
        {
            preferences[ranks[k]][ranks[n - l]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // for each candidate pair, checks the preferred candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences [j][i])
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
    // establish pair cache to store the pair values which will be swapped out during sort
    pair pair_cache[MAX * (MAX - 1) / 2];
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if ((preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]) >
                (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]))
            {
                pair_cache[i].winner = pairs[i].winner;
                pair_cache[i].loser = pairs[i]. loser;

                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                pairs[j].winner = pair_cache[i].winner;
                pairs[j].loser = pair_cache[i].loser;
            }
        }
    }
    return;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // each sorted pair starts being 'allowed' i.e. true
    bool allowed;
    for (int i = 0; i < pair_count; i++)
    {
        allowed = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // checks if the winner of pairs[i] has previously lost
            if (locked[j][pairs[i].winner])
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    // if so, checks if the loser of pairs[i] has ever won
                    if (locked[pairs[i].loser][k])
                    {
                        // if so, checks if the loser has already beaten the person who beat the winner
                        // also checks if the loser and person who beat the winner are the same
                        // actually doesn't work for loops larger than 4..
                        if ((locked[k][j]) || (k == j))
                        {
                            allowed = false;
                        }
                    }
                }
            }
        }

        if (allowed)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // establish if candidate is a source and makes array which defines number of times its a source
    bool source_check;
    int source[candidate_count];

    // populates array with 0 for each candidate to start
    for (int i = 0; i < candidate_count; i++)
    {
        source[i] = 0;
    }

    for (int i = 0; i < pair_count; i++)
    {
        // starts with each candidate being a source
        source_check = true;
        for (int j = 0; j < pair_count; j++)
        {
            // but sets to false if candidate has ever lost
            if (locked[j][pairs[i].winner])
            {
                source_check = false;
            }
        }
        // if winner is source compatible and is a locked pair then adds a source count
        if ((source_check) && (locked[pairs[i].winner][pairs[i].loser]))
        {
            source[pairs[i].winner]++;
        }
    }

    int win_count = 0;
    // finds the highest source count(s)
    for (int i = 0; i < candidate_count; i++)
    {
        if (source[i] > win_count)
        {
            win_count = source[i];
        }
    }
    // prints all candidates with the highest source counts
    for (int i = 0; i < candidate_count; i++)
    {
        if (source[i] == win_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}