#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "board.h"

typedef enum{
    EAGLE,
    TAILS
}coin;

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

bool move_user(size_t n, big_board *boards, tic_tac_toe symbol_for_moving){
    if(boards->next_col == -1 && boards->next_row == -1){
        n--;
        if(boards->boards[big_r][big_c].cells[small_r][small_c] != EMPTY) return false;
        if (boards->boards[big_r][big_c].winner != EMPTY) return false;
        boards->boards[big_r][big_c].cells[small_r][small_c] = symbol_for_moving;
        boards->next_col = small_c;
        boards->next_row = small_r;
        return true;
    }else{
        size_t start = (boards->next_row * 27) + (boards->next_col * 9) + 1;
        size_t end = start + 8;
        if(n > end || n < start) return false;
        if(boards->boards[big_r][big_c].cells[small_r][small_c] != EMPTY) return false;
        if (boards->boards[big_r][big_c].winner != EMPTY) return false;
        boards->boards[big_r][big_c].cells[small_r][small_c] = symbol_for_moving;
        boards->next_col = small_c;
        boards->next_row = small_r;
        return true;
    }
}
