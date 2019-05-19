#include "testHelper.h"
#include "dominion.h"
#include <stdio.h>

void printCorrect() {
  printf("\033[0;32m");
  printf("  Correct!\n");
  printf("\033[0m");
}

void printFailure() {
  printf("\033[0;31m");
  printf("  Failed!\n");
  printf("\033[0m");
}

int getSupplyCount(struct gameState *g) {
  int i, total = 0;
  for (i = 0; i < treasure_map+1; i++) {
    if (g->supplyCount[i] > 0) {
      total += g->supplyCount[i]; 
    }
  }
  return total;
}

void myAssert(int t) {
  if (t)
    printCorrect();
  else
    printFailure();
}
