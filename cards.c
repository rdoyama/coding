/* Use of struct to draw 7 different cards from a normal deck
and calculate the probabilities of a few combinations using
Monte Carlo.

Cards values are represented by integers ranging form 0 (two) to
twelve (ace), while suits are from 0 (clubs) to 3 (spades), both
are sorted from lower to higher.

For the calculation of the probabilities, we assume that there 
isn't a suit hierarchy, as the way it works in the most
common poker variants. The code finds combinations sorting
the list of card values in a given hand and counting the 
occurrences of cards of the same value.

Combinations: 4 of a kind, Full house, 3 of a kind, 2 pairs,
1 pair, 0 pairs. Note: The resulting combination is the higher
that the player can get with 5 cards.

Sorting Algorithm: Mergesort 

Running Time: less than 10 seconds with GENERATED_HANDS = 1e7
              approx. 1 second with GENERATED_HANDS = 1e6
              3.4 GHz CPU

To compile: gcc cards.c -o cards */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N_VAL 13
#define N_SUITS 4
#define HAND_SIZE 7
#define RANDOMV rand() % N_VAL
#define RANDOMS rand() % N_SUITS
#define GENERATED_HANDS 10000000

// Use of enum to represent card values
// As cards are generated using integers, this is not
// really necessary, but it is requested in the exercise
typedef enum card_values {two, three, four, five, six, seven,
        eight, nine, ten, jack, queen, king, ace} card_values;

// Use of enum to represent card suits
// As cards are generated using integers, this is not
// really necessary, but it is requested in the exercise
typedef enum card_suits {clubs, diamonds, hearts, spades} card_suits;

// Use of enum to represent combinations, from lower to higher
// np = No Pairs, op = One Pair, ..., fk = Four of a Kind
typedef enum combinations {np, op, tp, tk, fh, fk} combinations;

// Cards are represented by values and suits, in this order
typedef struct card
{
    card_values v;
    card_suits s;
} card;

// Prints the value of a card (e.g. "Ace of Spades")
void print_card(card *c)
{
    int val = c -> v, suit = c -> s;
    switch(val)
    {
        case 0: printf("2 of "); break;
        case 1: printf("3 of "); break;
        case 2: printf("4 of "); break;
        case 3: printf("5 of "); break;
        case 4: printf("6 of "); break;
        case 5: printf("7 of "); break;
        case 6: printf("8 of "); break;
        case 7: printf("9 of "); break;
        case 8: printf("10 of "); break;
        case 9: printf("Jack of "); break;
        case 10: printf("Queen of "); break;
        case 11: printf("King of "); break;
        case 12: printf("Ace of "); break;
    }
    switch(suit)
    {
        case 0: printf("Diamonds\n"); break;
        case 1: printf("Spades\n"); break;
        case 2: printf("Hearts\n"); break;
        case 3: printf("Clubs\n"); break;
    }
}

// Checks if two cards are the same. Returns 1 if so and
// 0 otherwise.
int equal(card card1, card card2)
{
    if (card1.v == card2.v && card1.s == card2.s)
        return 1;
    return 0;
}

// Checks if a given card is already in the hand, returning 1
// if so and 0 otherwise.
int pick_in_hand(card pick, card hand[], int i)
{
    int j;
    if (i == 0)
        return 0;
    for (j=0; j < i; j++)
    {
        if (equal(pick, hand[j]))
            return 1;
    }
    return 0;
}

// Generates a hand with HAND_SIZE random cards from a normal deck.
void gen_hand(card hand[HAND_SIZE])
{
    card pick;
    int i, repeat = 1;
    for (i=0; i < HAND_SIZE; i++)
    {
        while (repeat != 0)
        {
            // Pick a card
            pick = (card){.v = RANDOMV, .s = RANDOMS};
            // If it is not in the hand, add it
            if (!(pick_in_hand(pick, hand, i)))
            {
                hand[i] = pick;
                repeat = 0;
            }            
        }
        repeat = 1;
    }
}

// Merge function for merge_sort
void merge(int array[], int left, int middle, int right)
{
    int i, j, k;
    int n_left = middle - left + 1;
    int n_right = right - middle;
    int L[n_left], R[n_right];

    // Separates left and right arrays
    for (i=0; i < n_left; i++)
        L[i] = array[left + i];
    for (j=0; j < n_right; j++)
        R[j] = array[middle + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    // Merging left and right arrays
    while (i < n_left && j < n_right)
    {
        if (L[i] < R[j])
            array[k] = L[i++];
        else
            array[k] = R[j++];
        k++;
    }

    // Add remaining elements
    while (i < n_left)
        array[k++] = L[i++];
    while (j < n_right)
        array[k++] = R[j++];
}

// MergeSort Algorithm
void merge_sort(int array[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);

        merge(array, left, middle, right);
    }
}

// Given a hand with HAND_SIZE cards, returns the combination
// with higher value in this hand.
combinations hand_result(card hand[HAND_SIZE])
{
    int card_values[HAND_SIZE];
    int twos=0, threes=0, fours=0;
    int i, j=1;
    
    // Adds card values to card_values array
    for (i=0; i < HAND_SIZE; i++)
        card_values[i] = hand[i].v;

    // Sorting
    merge_sort(card_values, 0, HAND_SIZE-1);

    // Counts occurrences of pairs, threes, and fours
    for (i=0; i < HAND_SIZE; i++)
    {
        if (card_values[i] == card_values[i+1] && i != HAND_SIZE - 1)
            j++;
        else
        {
            switch(j)
            {
                case 4: return fk;
                case 3: threes++; break;
                case 2: twos++; break;
            }
            j = 1;
        }
    }

    // Resulting combinations from high to low
    if (threes != 0 && twos != 0)
        return fh;
    else if (threes != 0 && twos == 0)
        return tk;
    else if (twos >= 2)
        return tp;
    else if (twos == 1)
        return op;
    else if (twos == 0)
        return np;
}

// Auxiliary function: prints the name of the given combination
void print_comb(combinations comb)
{
    switch(comb)
    {
        case 0: printf("No Pairs\n"); break;
        case 1: printf("One Pair\n"); break;
        case 2: printf("Two Pairs\n"); break;
        case 3: printf("Three of a Kind\n"); break;
        case 4: printf("Full House\n"); break;
        case 5: printf("Four of a Kind\n"); break;
    }
}

int main(void)
{
    card my_hand[HAND_SIZE] = {0};
    int i, j;
    int np=0, op=0, tp=0, tk=0, fh=0, fk=0;
    float pnp, pop, ptp, ptk, pfh, pfk;
    combinations comb;

    // Loop to generate hands and count the results
    for (j=0; j < GENERATED_HANDS; j++)
    {
        // Seed, using "+j" to avoid repetitions
        srand(time(0)+j);
        gen_hand(my_hand);

        comb = hand_result(my_hand);
        switch(comb)
        {
            case 0: np++; break;
            case 1: op++; break;
            case 2: tp++; break;
            case 3: tk++; break;
            case 4: fh++; break;
            case 5: fk++; break;
        }
    }

    // Results and comments
    printf("\nCombinations\t\tProbability\tTheoretical\n");
    pnp = (float)np / GENERATED_HANDS;
    printf("No Pairs\t\t= %f\t0.174119\n", pnp);
    pop = (float)op / GENERATED_HANDS;
    printf("One Pair\t\t= %f\t0.438225\n", pop);
    ptp = (float)tp / GENERATED_HANDS;
    printf("Two Pairs\t\t= %f\t0.234955\n", ptp);
    ptk = (float)tk / GENERATED_HANDS;
    printf("Three of a Kind\t\t= %f\t0.048299\n", ptk);
    pfh = (float)fh / GENERATED_HANDS;
    printf("Full House\t\t= %f\t0.025961\n", pfh);
    pfk = (float)fk / GENERATED_HANDS;
    printf("Four of a Kind\t\t= %f\t0.001681\n", pfk);

    printf("\nTotal\t\t\t= %f\n", pnp+pop+ptp+ptk+pfh+pfk);

    printf("\n\nNote that the probabilities are slightly\n");
    printf("different form the theoretical values. This\n");
    printf("happens because we're not counting all\n");
    printf("combinations (e.g. flush, straight). These\n");
    printf("adds to the combinations used, increasing\n");
    printf("their values.\n");

    return 0;

}