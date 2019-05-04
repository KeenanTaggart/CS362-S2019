/* Author: Keenan Taggart
 * Class: CS 362
 * Date: May 5, 2019
 * Description: First unit test for Assignment 3, 2a
 *   This will be testing functionality of the refactored Smithy card effect.
 *   What follows is a positive test suite.
 *
 *   Inspiration for this unit test was taken from cardtest4.c, provided in
 *   the class files. As such much of the code will bear some similarities.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "testHelper.h"     // Contains functions for printing/counting used in all tests

int main() {
  struct gameState g, test_g;
  int players = 2, current_player = 0, seed = 100, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int opponent = 1;
  int supply_set[10] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, great_hall};

  initializeGame(players, supply_set, seed, &g);

  printf("\n---------- UNIT TEST: Smithy ----------\n\n");
  printf("Test 1: Play smithy from a fresh game state.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] + 3 - 1);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] + 3 - 1);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      g.deckCount[current_player] - 3);
  myAssert(test_g.deckCount[current_player] == g.deckCount[current_player] - 3);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 1);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 1);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g));
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g));

  printf("Checking game state of opponent ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[opponent],
      g.handCount[opponent]);
  myAssert(test_g.handCount[opponent] == g.handCount[opponent]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[opponent],
      g.deckCount[opponent]);
  myAssert(test_g.deckCount[opponent] == g.deckCount[opponent]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[opponent],
      g.discardCount[opponent]);
  myAssert(test_g.discardCount[opponent] == g.discardCount[opponent]);

  printf("\nTest 2: Play smithy twice from a fresh game state.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &test_g, handPos, &bonus);
  cardEffect(smithy, choice1, choice2, choice3, &test_g, handPos, &bonus);
  
  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] + 6 - 2);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] + 6 - 2);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      g.deckCount[current_player] - 5);
  myAssert(test_g.deckCount[current_player] == g.deckCount[current_player] - 5);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 1);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 2);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g));
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g));

  printf("Checking game state of opponent ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[opponent],
      g.handCount[opponent]);
  myAssert(test_g.handCount[opponent] == g.handCount[opponent]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[opponent],
      g.deckCount[opponent]);
  myAssert(test_g.deckCount[opponent] == g.deckCount[opponent]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[opponent],
      g.discardCount[opponent]);
  myAssert(test_g.discardCount[opponent] == g.discardCount[opponent]);
}
