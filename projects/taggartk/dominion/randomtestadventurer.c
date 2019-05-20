/* Author: Keenan Taggart
 * Class: CS 362
 * Date: May 19, 2019
 * Description: Third random card test for Assignment 4
 *   This will be random tests of the Adventurer card effect
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
    deck[i] = supply[rand() % 13];
  }
}

int numTreasures(int deck[], int sz) {
  int i, total = 0;
  for (i = 0; i < sz; i++) {
    if (deck[i] == copper ||
        deck[i] == silver ||
        deck[i] == gold)
      total++;
  }
  return total;
}

int numCoin(int deck[], int sz, int coin) {
  int i, total = 0;
  for (i = 0; i < sz; i++) {
    if (deck[i] == coin)
      total++;
  }
  return total;
}

int main() {
  struct gameState g, test_g;
  int current_player = 0, seed = 100, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int supply_set[10] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, treasure_map};
  int deck_seed_set[13] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, treasure_map, gold, silver, copper};

  int i, j, k, l;

  int players, r_handsize, r_decksize, r_discardsize, r_playedtimes;
  int end_handsz, end_decksz, end_discardsz, total_treasures;
  srand(time(0));
  printf("\n---------- RANDOM TESTS: Adventurer ----------\n\n");

  for (i = 0; i < ITERATIONS; i++) {
    printf("\n--- Iteration %d ---\n", i+1);
    players = (rand() % 3) + 2;
    initializeGame(players, supply_set, seed, &g);
    // memcpy(&test_g, &g, sizeof(struct gameState));
    g.numActions  = (rand() % RAND_RANGE);
    g.coins       = (rand() % RAND_RANGE);
    g.numBuys     = (rand() % RAND_RANGE);
    r_handsize    = (rand() % RAND_RANGE);
    r_decksize    = (rand() % RAND_RANGE);
    r_discardsize = (rand() % RAND_RANGE);

    for (j = 0; j < players; j++) {
      g.handCount[j]    = r_handsize;
      g.deckCount[j]    = r_decksize;
      g.discardCount[j] = r_discardsize;
      randDeck(g.hand[j], r_handsize, deck_seed_set);
      randDeck(g.deck[j], r_decksize, deck_seed_set);
      randDeck(g.discard[j], r_discardsize, deck_seed_set);
    }
    memcpy(&test_g, &g, sizeof(struct gameState));
    if (r_handsize == 0)
      r_playedtimes = 0;
    else
      r_playedtimes = (rand() % r_handsize) + 1;

    printf("%d players, %d cards in hand, %d cards in deck, %d cards in discard (total: %d)\n", players, r_handsize, r_decksize, r_discardsize, r_handsize+r_decksize+r_discardsize);
    printf("%d coppers, %d silvers, %d golds in hand\n%d coppers, %d silvers, %d golds in deck\n%d coppers, %d silvers, %d golds in discard\n",
        numCoin(g.hand[current_player], g.handCount[current_player], copper), numCoin(g.hand[current_player], g.handCount[current_player], silver),
        numCoin(g.hand[current_player], g.handCount[current_player], gold), numCoin(g.deck[current_player], g.deckCount[current_player], copper),
        numCoin(g.deck[current_player], g.deckCount[current_player], silver), numCoin(g.deck[current_player], g.deckCount[current_player], gold),
        numCoin(g.discard[current_player], g.discardCount[current_player], copper), numCoin(g.discard[current_player], g.discardCount[current_player], silver),
        numCoin(g.discard[current_player], g.discardCount[current_player], gold));

    
    printf("Playing Adventurer %d times!\n", r_playedtimes);
    for (k = 0; k < r_playedtimes; k++) {
      cardEffect(adventurer, choice1, choice2, choice3, &test_g, handPos, &bonus);
    }
    printf("Treasure locations after playing Adventurer card(s):\n");
    printf("%d coppers, %d silvers, %d golds in hand\n%d coppers, %d silvers, %d golds in deck\n%d coppers, %d silvers, %d golds in discard\n",
        numCoin(test_g.hand[current_player], test_g.handCount[current_player], copper),       numCoin(test_g.hand[current_player], test_g.handCount[current_player], silver),
        numCoin(test_g.hand[current_player], test_g.handCount[current_player], gold),         numCoin(test_g.deck[current_player], test_g.deckCount[current_player], copper),
        numCoin(test_g.deck[current_player], test_g.deckCount[current_player], silver),       numCoin(test_g.deck[current_player], test_g.deckCount[current_player], gold),
        numCoin(test_g.discard[current_player], test_g.discardCount[current_player], copper), numCoin(test_g.discard[current_player], test_g.discardCount[current_player], silver),
        numCoin(test_g.discard[current_player], test_g.discardCount[current_player], gold));
    total_treasures = numTreasures(g.deck[current_player], g.deckCount[current_player])
        + numTreasures(g.discard[current_player], g.discardCount[current_player]);

    // If Adventurer tries for more treasures than available, gain only available
    if (r_playedtimes * 2 > total_treasures)
      end_handsz = g.handCount[current_player] + total_treasures - r_playedtimes; 
    else
      end_handsz = g.handCount[current_player] + r_playedtimes;

    printf("\nChecking state of active player:\n");
    printf("Current hand count: %d; Expected: %d\n", test_g.handCount[current_player], end_handsz);
    myAssert(test_g.handCount[current_player] == end_handsz);
    printf("Total cards in deck, discard: %d; Expected: %d\n", 
        test_g.deckCount[current_player] + test_g.discardCount[current_player],
        g.deckCount[current_player] + g.discardCount[current_player] - (end_handsz - r_handsize));
    myAssert(test_g.deckCount[current_player] + test_g.discardCount[current_player] ==
        g.deckCount[current_player] + g.discardCount[current_player] - (end_handsz - r_handsize));
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
