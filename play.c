#include <stdlib.h>
#include <stdbool.h>

static void seed_prng(void) {
  static bool seed = false;
  if (!seed) {
    srand(time(NULL));
    for (int i = 0; i < 50; i++)
      rand();
    seed = true;
  }
}

int random(int minimum, int maxaimum) {
  seed_prng();
  return rand() / (RAND_MAX / (maxaimum - minimum + 1) + 1) + minimum;
}

