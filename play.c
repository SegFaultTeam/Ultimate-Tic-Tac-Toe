#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "board.h"
#include <unistd.h>
#include <stdio.h>
typedef enum{
    EAGLE,
    TAILS
}coin;

//making random seed
static void seed_prng(void) {
  static bool seed = false;
  if (!seed) {
    srand(time(NULL));
    for (int i = 0; i < 50; i++)
      rand();
    seed = true;
  }
}

//using random seed for coin
int randkom(int minimum, int maxaimum) {
  seed_prng();
  return rand() / (RAND_MAX / (maxaimum - minimum + 1) + 1) + minimum;
}
