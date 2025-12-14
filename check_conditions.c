#include "board.h"
#include <stdbool.h>
bool check_win(big_board *board){
    for(int bigR = 0; bigR < 3; bigR++){
        for(int bigC = 0; bigC < 3; bigC++){
        if(board->boards[bigR][bigC].winner != EMPTY) continue;
            if (board->boards[bigR][bigC].cells[0][0] != EMPTY && board->boards[bigR][bigC].cells[0][0] == board->boards[bigR][bigC].cells[1][1] && board->boards[bigR][bigC].cells[0][0] == board->boards[bigR][bigC].cells[2][2]){
                board->boards[bigR][bigC].winner = board->boards[bigR][bigC].cells[0][0];
                    return true;
            }
            if (board->boards[bigR][bigC].cells[0][2] != EMPTY && board->boards[bigR][bigC].cells[0][2] == board->boards[bigR][bigC].cells[1][1] && board->boards[bigR][bigC].cells[0][2] == board->boards[bigR][bigC].cells[2][0]) {
                board->boards[bigR][bigC].winner = board->boards[bigR][bigC].cells[0][2];
                    return true;
            }
            for (int i = 0; i < 3; i++){
                if (board->boards[bigR][bigC].cells[i][0] != EMPTY && board->boards[bigR][bigC].cells[i][0] == board->boards[bigR][bigC].cells[i][1] && board->boards[bigR][bigC].cells[i][0] == board->boards[bigR][bigC].cells[i][2]){
                board->boards[bigR][bigC].winner = board->boards[bigR][bigC].cells[i][0]; 
                    return true;
                }
            }
            for (int i = 0; i < 3; i++){
                if (board->boards[bigR][bigC].cells[0][i] != EMPTY && board->boards[bigR][bigC].cells[0][i] == board->boards[bigR][bigC].cells[1][i] && board->boards[bigR][bigC].cells[0][i] == board->boards[bigR][bigC].cells[2][i]) {
                    board->boards[bigR][bigC].winner = board->boards[bigR][bigC].cells[0][i]; 
                    return true;
                }
            }
        }
    }
    return false;
}

tic_tac_toe check_full(const big_board board){
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