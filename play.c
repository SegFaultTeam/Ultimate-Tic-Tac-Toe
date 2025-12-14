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

void fallback(big_board * board, tic_tac_toe comp) { 
    int corners[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
    if(board->next_col == -1 && board->next_row == -1) { //first case if computer is not limited
        if(board->boards[1][1].cells[1][1] == EMPTY) { //checking if center is empty
            board->boards[1][1].cells[1][1] = comp;
            board->next_col = 1;
            board->next_row = 1;
            return;
        }

        for(int i = 0; i<4; i++) { //checking for big corners
            int bigRows = corners[i][0];
            int bigCols = corners[i][1];
            if(board->boards[bigRows][bigCols].cells[1][1] == EMPTY) {
                board->boards[bigRows][bigCols].cells[1][1] = comp;
                board->next_col = 1;
                board->next_row = 1;
                return;
            }
        } 
        for(int bigRows = 0; bigRows < 3; bigRows++) { //checking for centers in small squares
            for(int bigCols = 0; bigCols < 3; bigCols++) {
                if(board->boards[bigRows][bigCols].cells[1][1] == EMPTY) {
                    board->boards[bigRows][bigCols].cells[1][1] = comp;
                    board->next_row = 1;
                    board->next_col = 1;
                    return;
                }
            }
        }

        for(int bigRows = 0; bigRows < 3; bigRows++) { //checking for small corners
            for(int bigCols = 0; bigCols < 3; bigCols++) {
                for(int i = 0; i < 4; i++) {
                    int rows = corners[i][0];
                    int cols = corners[i][1];
                    if(board->boards[bigRows][bigCols].cells[rows][cols] == EMPTY) {
                        board->boards[bigRows][bigCols].cells[rows][cols] = comp;
                        board->next_col = cols;
                        board->next_row = rows;
                        return;
                    }
                }
            }
        }

          for(int bigRows = 0; bigRows < 3; bigRows++) { //picking first non empty
            for(int bigCols = 0; bigCols < 3; bigCols++) {
                for(int smallRows = 0; smallRows < 3; smallRows++) {
                    for(int smallCols = 0; smallCols < 3; smallCols++){
                        if(board->boards[bigRows][bigCols].cells[smallRows][smallCols] == EMPTY) {
                            board->boards[bigRows][bigCols].cells[smallRows][smallCols] = comp;
                            board->next_row = smallRows;
                            board->next_col = smallCols;
                            return;
                        }
                    }
                }
            }
            
        }
    }

    else { //second case if computer is limited in one particular board
        if(board->boards[board->next_row][board->next_col].cells[1][1] == EMPTY) { //searching for center as second priority
            board->boards[board->next_row][board->next_col].cells[1][1] = comp;
            board->next_row = 1;
            board->next_col = 1;
            return;
        }
       
        for(int i = 0; i < 4; i++) { //searching for corners as third priority
            int rows = corners[i][0];
            int cols = corners[i][1];
            if(board->boards[board->next_row][board->next_col].cells[rows][cols] == EMPTY) {
                board->boards[board->next_row][board->next_col].cells[rows][cols] = comp;
                board->next_row = rows;
                board->next_col = cols;
                return;
            } 
        }
        for(int rows = 0 ; rows < 3; rows++) { //in other cases marking first non-empty place
            for(int cols = 0; cols < 3; cols++) {
                if(board->boards[board->next_row][board->next_col].cells[rows][cols] == EMPTY) {
                    board->boards[board->next_row][board->next_col].cells[rows][cols] = comp;
                    board->next_row = rows;
                    board->next_col = cols;
                    return;
                }
            }
        }
    }
}

void computer_logic(big_board *board, tic_tac_toe comp) {

    tic_tac_toe user = comp == O ? X : O;

    if(board->next_col == -1 && board->next_row == -1) { //if computes is allowed to tick at any board
        for(int bigRow = 0; bigRow < 3; bigRow++) {
                for(int bigCol = 0; bigCol < 3; bigCol++) {
                    
                    for(int smallRow = 0; smallRow < 3; smallRow++) { //first case, searching if in row there are two X or O, setting this as a priority one
                         int emptyRow = -1;
                        int emptyCol = -1;
                        int countComp = 0;
                        int countUser = 0;

                    for(int smallCol = 0; smallCol < 3; smallCol++) {
                        if(board->boards[bigRow][bigCol].cells[smallRow][smallCol] == EMPTY) {
                            emptyRow = smallRow;
                            emptyCol = smallCol;
                        } else if(board->boards[bigRow][bigCol].cells[smallRow][smallCol] == user) {
                            countUser++;
                        } else countComp++;
                    }

                    if(emptyCol != -1 && ((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2))) {
                        board->boards[bigRow][bigCol].cells[emptyRow][emptyCol] = comp;
                        board->next_row = emptyRow;
                        board->next_col = emptyCol;
                        return;
                    }
                }
                for(int smallCol = 0; smallCol < 3; smallCol++) { //first case, searching if in col there are two X or O, setting this as a priority one
                    int countComp = 0;
                    int countUser = 0;
                    int emptyRow = -1;

                    for(int smallRow = 0; smallRow < 3; smallRow++) {
                        if(board->boards[bigRow][bigCol].cells[smallRow][smallCol] == EMPTY) {
                            emptyRow = smallRow;
                        } else if(board->boards[bigRow][bigCol].cells[smallRow][smallCol] == user) {
                            countUser++;
                        } else countComp++;
                    }

                    if(emptyRow != -1 && ((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2))) {
                        board->boards[bigRow][bigCol].cells[emptyRow][smallCol] = comp;
                        board->next_row = emptyRow;
                        board->next_col = smallCol;
                        return;
                    }
                }
            //first case, searching if in diagonale there are two X or O, setting this as a priority one

                int emptyRow = -1;
                int emptyCol = -1;
                int countComp = 0;
                int countUser = 0;

            for(int i = 0; i < 3; i++) { 
                if(board->boards[bigRow][bigCol].cells[i][i] == EMPTY) {
                    emptyRow = i;
                    emptyCol = i;
                } else if(board->boards[bigRow][bigCol].cells[i][i] == user) {
                    countUser++;
                } else countComp++;
            }

            if(emptyCol != -1 && ((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2))) {
                board->boards[bigRow][bigCol].cells[emptyRow][emptyCol] = comp;
                board->next_row = emptyRow;
                board->next_col = emptyCol;
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

            if(emptyCol != -1 && ((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2))) {
                board->boards[bigRow][bigCol].cells[emptyRow][emptyCol] = comp;
                board->next_row = emptyRow;
                board->next_col = emptyCol;
                return;
            }
        }
    }
}
else { //second case if computer is limited in one particular board
    for(int smallRow = 0; smallRow < 3; smallRow++) {
        int emptyCol = -1;
        int countComp = 0;
        int countUser = 0;
        int emptyRow = -1;
        for(int smallCol = 0; smallCol < 3; smallCol++) { //searching in row for two O or X
            if(board->boards[board->next_row][board->next_col].cells[smallRow][smallCol] == EMPTY) {
                emptyCol = smallCol;
                emptyRow = smallRow;
            } 
            else if(board->boards[board->next_row][board->next_col].cells[smallRow][smallCol] == user) countUser++;
            else countComp++;
        }

            if(emptyCol != -1 && ((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2))) {
                board->boards[board->next_row][board->next_col].cells[emptyRow][emptyCol] = comp;
                board->next_row = emptyRow;
                board->next_col = emptyCol;
                return;
            }
        
    }
    

    for(int smallCol = 0; smallCol < 3; smallCol++) { //searching in col for two O or X
        int emptyRow = -1;
        int countComp = 0;
        int countUser = 0;
        for(int smallRow = 0; smallRow < 3; smallRow++) {
            if(board->boards[board->next_row][board->next_col].cells[smallRow][smallCol] == EMPTY) {
                emptyRow = smallRow;
            } 
            else if(board->boards[board->next_row][board->next_col].cells[smallRow][smallCol] == user) countUser++;
            else countComp++;
        }
        if(emptyRow != -1 && ((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2))) {
                board->boards[board->next_row][board->next_col].cells[emptyRow][smallCol] = comp;
                board->next_row = emptyRow;
                board->next_col = smallCol;
                return;
            }
    }

                int emptyRow = -1;
                int emptyCol = -1;
                int countComp = 0;
                int countUser = 0;
    //searching for two X or O in diagonale
            for(int i = 0; i < 3; i++) {
                if(board->boards[board->next_row][board->next_col].cells[i][i] == EMPTY) {
                    emptyRow = i;
                    emptyCol = i;
                } else if(board->boards[board->next_row][board->next_col].cells[i][i] == user) {
                    countUser++;
                } else countComp++;
            }

            if(emptyCol != -1 && ((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2))) {
                board->boards[board->next_row][board->next_col].cells[emptyRow][emptyCol] = comp;
                board->next_row = emptyRow;
                board->next_col = emptyCol;
                return;
            }

            countComp = countUser = 0;
            emptyRow = -1;
            emptyCol = -1;

            for(int i = 0; i < 3; i++) {
                if(board->boards[board->next_row][board->next_col].cells[i][2-i] == EMPTY) {
                    emptyRow = i;
                    emptyCol = 2 - i;
                } else if(board->boards[board->next_row][board->next_col].cells[i][2-i] == user) {
                    countUser++;
                } else countComp++;
            }

            if(emptyCol != -1 && ((countComp == 2 && countUser == 0) || (countComp == 0 && countUser == 2))) {
                board->boards[board->next_row][board->next_col].cells[emptyRow][emptyCol] = comp;
                board->next_row = emptyRow;
                board->next_col = emptyCol;
                return;
            }

            //if there are none, calling fallback
            fallback(board, comp);
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


