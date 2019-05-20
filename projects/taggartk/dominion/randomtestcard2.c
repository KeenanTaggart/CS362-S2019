/* Author: Keenan Taggart
 * Class: CS 362
 * Date: May 19, 2019
 * Description: Second random card test for Assignment 4
 *   This will be random tests of the Treasure Map card effect
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
    deck[i] = supply[rand() % 11];
  }
}

int numMaps(int hand[], int sz) {
  int i, total = 0;
  for (i = 0; i < sz; i++) {
    if (hand[i] == treasure_map)
     total++; 
  }
  return total;
}

// Returns an index for a treasure map card in hand
int findMap(int hand[], int sz) {
  int i;
  for (i = 0; i < sz; i++) {
    if (hand[i] == treasure_map)
      return i;
  }
  return -1;
}

int numGolds(int deck[], int sz) {
  int i, total = 0;
  for (i = 0; i < sz; i++) {
    if (deck[i] == gold)
      total++;
  }
  return total;
}

int main() {
  struct gameState g, test_g;
  int current_player = 0, seed = 100, /*handPos = 0,*/ choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int supply_set[10] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, treasure_map};
  int deck_seed_set[11] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, treasure_map, gold};

  int i, j, k, l;

  int players, r_handsize, r_decksize, r_discardsize, r_playedtimes;
  int end_gold;
  int mapsInHand;
  srand(time(0));
  printf("\n---------- RANDOM TESTS: Treasure Map ----------\n\n");

  for (i = 0; i < ITERATIONS; i++) {
    printf("--- Iteration %d ---\n", i+1);
    players = (rand() % 3) + 2;
    initializeGame(players, supply_set, seed, &g);
    memcpy(&test_g, &g, sizeof(struct gameState));

    g.numActions = test_g.numActions = (rand() % RAND_RANGE);
    g.coins = test_g.coins           = (rand() % RAND_RANGE);    // 0 - 99 coins
    g.numBuys = test_g.numBuys       = (rand() % RAND_RANGE);    // 0 - 99 buys
    r_handsize                       = (rand() % RAND_RANGE);                       
    r_decksize                       = (rand() % RAND_RANGE);
    r_discardsize                    = (rand() % RAND_RANGE);
    g.supplyCount[gold] = test_g.supplyCount[gold] = (rand() % RAND_RANGE);
    
    for (j = 0; j < players; j++) {                              // Same values for each player in the game
      g.handCount[j] = test_g.handCount[j]       = r_handsize;
      g.deckCount[j] = test_g.deckCount[j]       = r_decksize;
      g.discardCount[j] = test_g.discardCount[j] = r_discardsize;

      randDeck(g.hand[j], r_handsize, deck_seed_set);
      randDeck(g.deck[j], r_decksize, deck_seed_set);
      randDeck(g.discard[j], r_discardsize, deck_seed_set);
    }
    memcpy(&test_g, &g, sizeof(struct gameState));
    // We play all the Treasure Maps in hand
    mapsInHand = numMaps(g.hand[current_player], r_handsize);
    r_playedtimes = mapsInHand / 2 + mapsInHand % 2;

    printf("%d players, %d cards in hand, %d cards in deck, %d cards in discard (total: %d)\n", players, r_handsize, r_decksize, r_discardsize, r_handsize+r_decksize+r_discardsize);
    printf("There are %d Treasure Maps in hand!\n", mapsInHand);
    printf("There are %d Golds in the supply and %d in the deck!\n", g.supplyCount[gold], numGolds(g.deck[current_player], g.deckCount[current_player]));

    for (k = 0; k < r_playedtimes; k++) {
      cardEffect(treasure_map, choice1, choice2, choice3, &test_g, findMap(test_g.hand[current_player], test_g.handCount[current_player]), &bonus);
    }

    // If Maps would give more gold than is in supply, then only gain amt in supply
    if (g.supplyCount[gold] > (mapsInHand / 2) * 4)
      end_gold = (mapsInHand / 2) * 4;
    else
      end_gold = g.supplyCount[gold];

    printf("\nChecking state of active player:\n");
    printf("Current hand count: %d; Expected: %d\n", test_g.handCount[current_player], g.handCount[current_player] - mapsInHand);
    myAssert(test_g.handCount[current_player] == g.handCount[current_player] - mapsInHand);
    printf("Total cards in hand, deck, discard: %d; Expected: %d\n", 
        test_g.handCount[current_player] + test_g.deckCount[current_player] + test_g.discardCount[current_player],
        g.handCount[current_player] + g.deckCount[current_player] + g.discardCount[current_player] + end_gold - mapsInHand);
    myAssert(test_g.handCount[current_player] + test_g.deckCount[current_player] + test_g.discardCount[current_player] ==
        g.handCount[current_player] + g.deckCount[current_player] + g.discardCount[current_player] + end_gold - mapsInHand);
    printf("Golds in deck: %d; Expected: %d\n", numGolds(test_g.deck[current_player], test_g.deckCount[current_player]), numGolds(g.deck[current_player], g.deckCount[current_player]) + end_gold);
    myAssert(numGolds(test_g.deck[current_player], test_g.deckCount[current_player]) == numGolds(g.deck[current_player], g.deckCount[current_player]) + end_gold);
    printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
    myAssert(test_g.coins == g.coins);
    printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
    myAssert(test_g.numBuys == g.numBuys);

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
