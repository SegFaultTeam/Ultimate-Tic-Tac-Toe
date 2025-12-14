#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "board.h"
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
void computer_logic(big_board board, tic_tac_toe c) {
if(board.next_col == 0 && board.next_row ==0) {

}
}
bool first_move_user(size_t n, big_board *boards, tic_tac_toe symbol_for_moving){
    if(boards->next_col == -1 && boards->next_row == -1){
        if (n < 1 || n > 81) return false;
        n--;
        size_t big_r   = n / 27;      
        size_t big_c   = (n / 9) % 3; 
        size_t small_r = (n / 3) % 3;
        size_t small_c = n % 3;
        boards[big_r][big_c]->cells[small_r][small_c] = symbol_for_moving;
    }
}
