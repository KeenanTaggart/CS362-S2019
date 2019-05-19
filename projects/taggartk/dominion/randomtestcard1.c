/* Author: Keenan Taggart
 * Class: CS 362
 * Date: May 19, 2019
 * Description: First random card test for Assignment 4
 *   This will be random tests of the Smithy card effect
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelper.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITERATIONS 10
#define RAND_RANGE 100

void randDeck(int deck[], int sz, int supply[10]) {
  int i;

  for (i = 0; i < sz; i++) {
    deck[i] = supply[rand() % 10];
  }
}

int main() {
  struct gameState g, test_g;
  // Most of what follows here is used in cards not being tested, so they are not randomized
  int current_player = 0, seed = 100, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int supply_set[10] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, great_hall};
  int i, j, k, l;

  int players, r_handsize, r_decksize, r_discardsize, r_playedtimes; 
  int end_handsz, end_decksz, end_discardsz;
  srand(time(0));
  printf("\n---------- RANDOM TESTS: Smithy ----------\n\n");
  
  for (i = 0; i < ITERATIONS; i++) {
    printf("--- Iteration %d ---\n", i+1);
    players = (rand() % 3) + 2;           // Random VALID # of players (2-4)
    initializeGame(players, supply_set, seed, &g);
    memcpy(&test_g, &g, sizeof(struct gameState));
    
    g.numActions = test_g.numActions = (rand() % RAND_RANGE);    // 0 - 99 actions default
    g.coins = test_g.coins           = (rand() % RAND_RANGE);    // 0 - 99 coins
    g.numBuys = test_g.numBuys       = (rand() % RAND_RANGE);    // 0 - 99 buys
    r_handsize    = (rand() % RAND_RANGE);                       
    r_decksize    = (rand() % RAND_RANGE);
    r_discardsize = (rand() % RAND_RANGE);
    for (j = 0; j < players; j++) {                              // Same values for each player in the game
      g.handCount[j] = test_g.handCount[j]       = r_handsize;
      g.deckCount[j] = test_g.deckCount[j]       = r_decksize;
      g.discardCount[j] = test_g.discardCount[j] = r_discardsize;

      // Smithy does not care about card permutations but for the sake of thoroughness
      randDeck(g.hand[j], r_handsize, supply_set);
      randDeck(test_g.hand[j], r_handsize, supply_set);
      randDeck(g.deck[j], r_decksize, supply_set);
      randDeck(test_g.deck[j], r_decksize, supply_set);
      randDeck(g.discard[j], r_discardsize, supply_set);
      randDeck(test_g.discard[j], r_discardsize, supply_set);
    }
    r_playedtimes = (rand() % r_handsize) + 1;                   // Playing more cards than are in hand leads to bad results 
    printf("%d players, %d cards in hand, %d cards in deck, %d cards in discard\n", players, r_handsize, r_decksize, r_discardsize);
    printf("Playing smithy %d times!\n", r_playedtimes);

    for (k = 0; k < r_playedtimes; k++) {
      cardEffect(smithy, choice1, choice2, choice3, &test_g, handPos, &bonus); 
    }

    // If we draw more than draw+discard, hand size will just be +(draw+discard)
    if (3 * r_playedtimes > (r_decksize + r_discardsize))
      end_handsz = r_handsize + r_decksize + r_discardsize - 1;
    else
      end_handsz = r_handsize + 3 * r_playedtimes - r_playedtimes;

    // Check player who played smithy cards
    printf("\nChecking state of active player:\n");
    printf("Current hand count: %d; Expected: %d\n", test_g.handCount[current_player], end_handsz);
    myAssert(test_g.handCount[current_player] == end_handsz);
    printf("Total cards in hand, deck, discard: %d; Expected: %d\n", 
        test_g.handCount[current_player] + test_g.deckCount[current_player] + test_g.discardCount[current_player],
        g.handCount[current_player] + g.deckCount[current_player] + g.discardCount[current_player]);
    myAssert(test_g.handCount[current_player] + test_g.deckCount[current_player] + test_g.discardCount[current_player] ==
        g.handCount[current_player] + g.deckCount[current_player] + g.discardCount[current_player]);
    printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
    myAssert(test_g.coins == g.coins);
    printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
    myAssert(test_g.numBuys == g.numBuys);

    // Check opponents. No values should be changed
    for (l = 1; l < players; l++) {
      printf("\nChecking state of opponent %d:\n", l+1);
      printf("Current hand count: %d; Expected: %d\n", test_g.handCount[l], g.handCount[l]);
      myAssert(test_g.handCount[l] == g.handCount[l]);
      printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[l],
          g.deckCount[l]);
      myAssert(test_g.deckCount[l] == g.deckCount[l]);
      printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[l],
          g.discardCount[l]);
      myAssert(test_g.discardCount[l] == g.discardCount[l]);
    }

  }
}


