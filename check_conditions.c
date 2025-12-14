#include "board.h"
check_win(big_board *board){
    for(int bigR = 0; bigR < 3; bigR++){
        for(int bigC = 0; bigC < 3; bigC++){
            for (int i = 0; i < 3; i++){
                if (board->boards[bigR][bigC].cells[i][0] != EMPTY)
            }
        }
    }
}