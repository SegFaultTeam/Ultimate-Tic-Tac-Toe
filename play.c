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

void computer_logic(big_board *board, tic_tac_toe comp){
    size_t countComp = 0;
    size_t countUser = 0;
    tic_tac_toe user = comp == O ? X : O;
    if(board->next_col == 0 && board->next_row == 0) {
        for(int bigRow = 0; bigRow < 3; bigRow++) {
            for(int smallRow = 0; smallRow < 3; smallRow++) {
                for(int bigCol = 0; bigCol < 3; bigCol++) {
                    int emptyRow = -1;
                    int emptyCol = -1;

                    for(int smallCol = 0; smallCol < 3; smallCol++) {
                        if(board->boards[bigRow][bigCol].cells[smallRow][smallCol] == EMPTY) {
                            emptyRow = smallRow;
                            emptyCol = smallCol;
                        } else if(board->boards[bigRow][bigCol].cells[smallRow][smallCol] == user) {
                            countUser++;
                        } else countComp++;
                    }

                    if((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2)) {
                        board->boards[bigRow][bigCol].cells[emptyRow][emptyCol] = comp;
                        return;
                    }
                }
            }

            for(int bigCol = 0; bigCol < 3; bigCol++) {
                for(int smallCol = 0; smallCol < 3; smallCol++) {
                    countComp = 0;
                    countUser = 0;
                    int emptyRow = -1;
                    int emptyCol = -1;

                    for(int smallRow = 0; smallRow < 3; smallRow++) {
                        if(board->boards[bigRow][bigCol].cells[smallRow][smallCol] == EMPTY) {
                            emptyRow = smallRow;
                            emptyCol = smallCol;
                        } else if(board->boards[bigRow][bigCol].cells[smallRow][smallCol] == user) {
                            countUser++;
                        } else countComp++;
                    }

                    if((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2)) {
                        board->boards[bigRow][bigCol].cells[emptyRow][emptyCol] = comp;
                        return;
                    }
                }
            }

            countComp = countUser = 0;
            int emptyRow = -1;
            int emptyCol = -1;

            for(int i = 0; i < 3; i++) {
                if(board->boards[bigRow][bigCol].cells[i][i] == EMPTY) {
                    emptyRow = i;
                    emptyCol = i;
                } else if(board->boards[bigRow][bigCol].cells[i][i] == user) {
                    countUser++;
                } else countComp++;
            }

            if((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2)) {
                board->boards[bigRow][bigCol].cells[emptyRow][emptyCol] = comp;
                return;
            }

            countComp = countUser = 0;
            emptyRow = -1;
            emptyCol = -1;

            for(int i = 0; i < 3; i++) {
                if(board->boards[bigRow][bigCol].cells[i][2-i] == EMPTY) {
                    emptyRow = i;
                    emptyCol = 2 - i;
                } else if(board->boards[bigRow][bigCol].cells[i][2-i] == user) {
                    countUser++;
                } else countComp++;
            }

            if((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2)) {
                board->boards[bigRow][bigCol].cells[emptyRow][emptyCol] = comp;
                return;
            }
        }
    }
}


bool move_user(size_t n, big_board *boards, tic_tac_toe symbol_for_moving){
    if(n>81 || n < 1) return false;
        n--;
        size_t big_r = n / 27;
        size_t big_c = (n / 9) % 3;
        size_t small_r = (n / 3) % 3;
        size_t small_c = n % 3;
    if(boards->next_col == -1 && boards->next_row == -1){
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


