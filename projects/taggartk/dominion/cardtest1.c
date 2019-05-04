/* Author: Keenan Taggart
 * Class: CS 362
 * Date: May 5, 2019
 * Description: First card test for Assignment 3, 2b
 *   This will be testing functionality of the Smithy card effect.
 *   What follows is a boundary test suite.
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
  int decksize1 = 3, decksize2 = 2, decksize3 = 1, decksize4 = 0;
  int supply_set[10] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, great_hall};

  initializeGame(players, supply_set, seed, &g);

  printf("\n---------- Card Test: Smithy ----------\n\n");
  printf("Test 1: Play Smithy when there are three cards in the player's deck.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  test_g.deckCount[current_player] = decksize1;
  cardEffect(smithy, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] - 1 + decksize1);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] - 1 + decksize1);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      decksize1 - 3);
  myAssert(test_g.deckCount[current_player] == decksize1 - 3);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 1);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 1);
  printf("Current actions: %d; Expected actions: %d\n", test_g.numActions, g.numActions);
  myAssert(test_g.numActions == g.numActions);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g));
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g));

  printf("Checking game state of opponent ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer]);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer]);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer]);

  printf("\nTest 2: Play Smithy when there are two cards in the player's deck.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  test_g.deckCount[current_player] = decksize2;
  cardEffect(smithy, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] - 1 + decksize2);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] - 1 + decksize2);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      decksize2 - 2);
  myAssert(test_g.deckCount[current_player] == decksize2 - 2);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 1);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 1);
  printf("Current actions: %d; Expected actions: %d\n", test_g.numActions, g.numActions);
  myAssert(test_g.numActions == g.numActions);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g));
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g));

  printf("Checking game state of opponent ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer]);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer]);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer]);

  printf("\nTest 3: Play Smithy when there is one card in the player's deck.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  test_g.deckCount[current_player] = decksize3;

  cardEffect(smithy, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] - 1 + decksize3);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] - 1 + decksize3);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      decksize3 - 1);
  myAssert(test_g.deckCount[current_player] == decksize3 - 1);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 1);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 1);
  printf("Current actions: %d; Expected actions: %d\n", test_g.numActions, g.numActions);
  myAssert(test_g.numActions == g.numActions);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g));
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g));

  printf("Checking game state of opponent ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer]);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer]);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer]);

  printf("\nTest 4: Play Smithy when there are no cards in the player's deck.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  test_g.deckCount[current_player] = decksize4;

  cardEffect(smithy, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] - 1);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] - 1);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      decksize4);
  myAssert(test_g.deckCount[current_player] == decksize4);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 1);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 1);
  printf("Current actions: %d; Expected actions: %d\n", test_g.numActions, g.numActions);
  myAssert(test_g.numActions == g.numActions);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g));
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g));

  printf("Checking game state of opponent ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer]);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer]);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer]);
}
