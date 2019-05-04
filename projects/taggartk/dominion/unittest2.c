/* Author: Keenan Taggart
 * Class: CS 362
 * Date: May 5, 2019
 * Description: Second unit test for Assignment 3, 2a
 *   This will be testing functionality of the refactored Tribute card effect.
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
  int players = 3, current_player = 0, seed = 50, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int nextPlayer = 1, lastPlayer = 2;  // 'next' performs tribute effect, 'last' does not
  int supply_set[10] = {adventurer, council_room, feast, gardens, smithy, mine, remodel, village, baron, great_hall};

  initializeGame(players, supply_set, seed, &g);

  printf("\n---------- UNIT TEST: Tribute ----------\n\n");
  printf("Test 1: Play tribute from a fresh game state. Revealed cards will be treasure and action.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  // Here we change the top cards of the next player's deck to a copper and adventurer
  test_g.deck[nextPlayer][test_g.deckCount[nextPlayer] - 1] = copper;
  test_g.deck[nextPlayer][test_g.deckCount[nextPlayer] - 2] = adventurer;
  cardEffect(tribute, choice1, choice2, choice3, &test_g, handPos, &bonus);

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
  printf("Current actions: %d; Expected actions: %d\n", test_g.numActions, g.numActions + 2);
  myAssert(test_g.numActions == g.numActions + 2);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins + 2);
  myAssert(test_g.coins == g.coins + 2);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g));
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g));

  printf("Checking game state of next player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer] - 2);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer] - 2);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer] + 2);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer] + 2);

  printf("Checking game state of third player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[lastPlayer],
      g.handCount[lastPlayer]);
  myAssert(test_g.handCount[lastPlayer] == g.handCount[lastPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[lastPlayer],
      g.deckCount[lastPlayer] - 2);
  myAssert(test_g.deckCount[lastPlayer] == g.deckCount[lastPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[lastPlayer],
      g.discardCount[lastPlayer]);
  myAssert(test_g.discardCount[lastPlayer] == g.discardCount[lastPlayer]);

  printf("\nTest 2: Play tribute from a fresh game state. Revealed cards will be action and victory point.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  test_g.deck[nextPlayer][test_g.deckCount[nextPlayer] - 1] = adventurer;
  test_g.deck[nextPlayer][test_g.deckCount[nextPlayer] - 2] = province;
  cardEffect(tribute, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] - 1 + 2);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] - 1 + 2);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      g.deckCount[current_player] - 2);
  myAssert(test_g.deckCount[current_player] == g.deckCount[current_player] - 2);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[current_player],
      g.discardCount[current_player] + 1);
  myAssert(test_g.discardCount[current_player] == g.discardCount[current_player] + 1);
  printf("Current actions: %d; Expected actions: %d\n", test_g.numActions, g.numActions + 2);
  myAssert(test_g.numActions == g.numActions + 2);
  printf("Current coins: %d; Expected coins: %d\n", test_g.coins, g.coins);
  myAssert(test_g.coins == g.coins);
  printf("Current buys: %d; Expected buys: %d\n", test_g.numBuys, g.numBuys);
  myAssert(test_g.numBuys == g.numBuys);
  printf("Total cards in supply: %d; Expected cards in supply: %d\n", getSupplyCount(&test_g),
      getSupplyCount(&g));
  myAssert(getSupplyCount(&test_g) == getSupplyCount(&g));

  printf("Checking game state of next player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer] - 2);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer] - 2);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer] + 2);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer] + 2);

  printf("Checking game state of third player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[lastPlayer],
      g.handCount[lastPlayer]);
  myAssert(test_g.handCount[lastPlayer] == g.handCount[lastPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[lastPlayer],
      g.deckCount[lastPlayer] - 2);
  myAssert(test_g.deckCount[lastPlayer] == g.deckCount[lastPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[lastPlayer],
      g.discardCount[lastPlayer]);
  myAssert(test_g.discardCount[lastPlayer] == g.discardCount[lastPlayer]);

  printf("\nTest 3: Play tribute from a fresh game state. Revealed cards will be two identical victory point cards.\n");
  memcpy(&test_g, &g, sizeof(struct gameState));

  test_g.deck[nextPlayer][test_g.deckCount[nextPlayer] - 1] = province;
  test_g.deck[nextPlayer][test_g.deckCount[nextPlayer] - 2] = province;
  cardEffect(tribute, choice1, choice2, choice3, &test_g, handPos, &bonus);

  printf("Checking game state of current player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[current_player],
      g.handCount[current_player] - 1 + 2);
  myAssert(test_g.handCount[current_player] == g.handCount[current_player] - 1 + 2);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[current_player],
      g.deckCount[current_player] - 2);
  myAssert(test_g.deckCount[current_player] == g.deckCount[current_player] - 2);
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

  printf("Checking game state of next player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[nextPlayer],
      g.handCount[nextPlayer]);
  myAssert(test_g.handCount[nextPlayer] == g.handCount[nextPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[nextPlayer],
      g.deckCount[nextPlayer] - 2);
  myAssert(test_g.deckCount[nextPlayer] == g.deckCount[nextPlayer] - 2);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[nextPlayer],
      g.discardCount[nextPlayer] + 2);
  myAssert(test_g.discardCount[nextPlayer] == g.discardCount[nextPlayer] + 2);

  printf("Checking game state of third player ---\n");
  printf("Current hand count: %d; Expected hand count: %d\n", test_g.handCount[lastPlayer],
      g.handCount[lastPlayer]);
  myAssert(test_g.handCount[lastPlayer] == g.handCount[lastPlayer]);
  printf("Current deck count: %d; Expected deck count: %d\n", test_g.deckCount[lastPlayer],
      g.deckCount[lastPlayer] - 2);
  myAssert(test_g.deckCount[lastPlayer] == g.deckCount[lastPlayer]);
  printf("Current discard count: %d; Expected discard count: %d\n", test_g.discardCount[lastPlayer],
      g.discardCount[lastPlayer]);
  myAssert(test_g.discardCount[lastPlayer] == g.discardCount[lastPlayer]);
}


