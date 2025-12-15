#include "board.h"
#include <stdbool.h>
bool check_win(big_board *board){
    for(int bigR = 0; bigR < 3; bigR++){
        for(int bigC = 0; bigC < 3; bigC++){

            small_board *sb = &board->boards[bigR][bigC];

            if(sb->winner != EMPTY)
                continue;

            if (sb->cells[0][0] != EMPTY &&
                sb->cells[0][0] == sb->cells[1][1] &&
                sb->cells[0][0] == sb->cells[2][2]) {
                sb->winner = sb->cells[0][0];
                return true;
            }

            if (sb->cells[0][2] != EMPTY &&
                sb->cells[0][2] == sb->cells[1][1] &&
                sb->cells[0][2] == sb->cells[2][0]) {
                sb->winner = sb->cells[0][2];
                return true;
            }
            for (int i = 0; i < 3; i++){
                if (sb->cells[i][0] != EMPTY &&
                    sb->cells[i][0] == sb->cells[i][1] &&
                    sb->cells[i][0] == sb->cells[i][2]) {
                    sb->winner = sb->cells[i][0];
                    return true;
                }
            }

            for (int i = 0; i < 3; i++){
                if (sb->cells[0][i] != EMPTY &&
                    sb->cells[0][i] == sb->cells[1][i] &&
                    sb->cells[0][i] == sb->cells[2][i]) {
                    sb->winner = sb->cells[0][i];
                    return true;
                }
            }

            bool has_empty = false;
            for (int r = 0; r < 3; r++){
                for (int c = 0; c < 3; c++){
                    if (sb->cells[r][c] == EMPTY) {
                        has_empty = true;
                        break;
                    }
                }
                if (has_empty) break;
            }

            if (!has_empty) {
                sb->winner = DRAW;
                return true;
            }
        }
    }
    return false;
}


tic_tac_toe check_full(const big_board *board){
    if(board->boards[1][1].winner != EMPTY){
        if(board->boards[0][0].winner == board->boards[1][1].winner && board->boards[1][1].winner == board->boards[2][2].winner) return board->boards[1][1].winner;
        else if(board->boards[0][2].winner == board->boards[1][1].winner && board->boards[1][1].winner == board->boards[2][0].winner) return board->boards[1][1].winner;
    }
    for (int bigR = 0; bigR < 3; bigR++){
        if(board->boards[bigR][0].winner != EMPTY && board->boards[bigR][0].winner == board->boards[bigR][1].winner && board->boards[bigR][0].winner == board->boards[bigR][2].winner) return board->boards[bigR][0].winner;
    }
    for (int bigC = 0; bigC < 3; bigC++){
        if(board->boards[0][bigC].winner != EMPTY && board->boards[0][bigC].winner == board->boards[1][bigC].winner && board->boards[0][bigC].winner == board->boards[2][bigC].winner) return board->boards[0][bigC].winner;
    }
    return EMPTY;  
}