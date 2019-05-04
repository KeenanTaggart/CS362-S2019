/* Author: Keenan Taggart
 * Class: CS 362
 * Date: May 5, 2019
 * Description: Third unit test for Assignment 3, 2a
 *   This will be testing functionality of the refactored Sea hag card effect.
 *   What follows is a positive test suite.
 *
 *   Inspiration for this unit test was taken from cardtest4.c, provided in
 *   the class files. As such, much of the code will bear some similarities.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "testHelper.h"

int main() {
  struct gameState g, test_g;
  int players = 2, current_player = 0, seed = 50, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int nextPlayer = 1;  
  int supply_set[10] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, great_hall};

  initializeGame(players, supply_set, seed, &g);

  printf("\n---------- UNIT TEST: Sea Hag ----------\n\n");
  printf("Test 1: Play Sea Hag from a fresh game state.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  cardEffect(sea_hag, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] - 1);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] - 1);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      g.deckCount[current_player]);
  myAssert(test_g.deckCount[current_player] == g.deckCount[current_player]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 1);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 1);
  printf("Current actions: %d; Expected actions: %d\n", test_g.numActions, g.numActions);
  myAssert(test_g.numActions == g.numActions);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Curses in supply: %d; Expected # in supply: %d\n", test_g.supplyCount[curse],
      g.supplyCount[curse] - 1);
  myAssert(test_g.supplyCount[curse] == g.supplyCount[curse] - 1);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g) - 1);
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g) - 1);

  printf("Checking game state of opponent ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer]);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer] + 1);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer] + 1);

  printf("\nTest 2: Play Sea Hag three times.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  cardEffect(sea_hag, choice1, choice2, choice3, &test_g, handPos, &bonus);
  cardEffect(sea_hag, choice1, choice2, choice3, &test_g, handPos, &bonus);
  cardEffect(sea_hag, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] - 3);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] - 3);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      g.deckCount[current_player]);
  myAssert(test_g.deckCount[current_player] == g.deckCount[current_player]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 3);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 3);
  printf("Current actions: %d; Expected actions: %d\n", test_g.numActions, g.numActions);
  myAssert(test_g.numActions == g.numActions);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Curses in supply: %d; Expected # in supply: %d\n", test_g.supplyCount[curse],
      g.supplyCount[curse] - 3);
  myAssert(test_g.supplyCount[curse] == g.supplyCount[curse] - 3);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g) - 3);
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g) - 3);

  printf("Checking game state of opponent ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer]);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer] + 3);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer] + 3);
}
