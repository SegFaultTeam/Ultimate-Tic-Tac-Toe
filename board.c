#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h> //for usleep func
#include <stdbool.h>
#include "raylib.h"

typedef enum{
    X,
    O,
    EMPTY
}tic_tac_toe;

typedef enum{
    player_1,
    player_2
}players_turn;

typedef struct{
    tic_tac_toe cells[3][3];
    tic_tac_toe winner;
}small_board;

typedef struct{
    small_board boards[3][3];
    players_turn current_player;
    size_t next_row, next_col;
}big_board;

void init(big_board * board) { //initting board with EMPTY type
    for(int bigRow = 0; bigRow < 3; bigRow++) {
    for(int smallRow = 0; smallRow < 3; smallRow++) {
    for(int bigCol = 0; bigCol < 3; bigCol++) {
        for(int smallCol = 0; smallCol < 3; smallCol++) {
            board->boards[bigRow][smallRow].cells[bigCol][smallCol] = EMPTY;
        }
    }
}
    }
}

void draw(big_board board) { // console version of drawing func
    system("clear");
    for(int bigRow = 0; bigRow < 3; bigRow++) {
    for(int smallRow = 0; smallRow < 3; smallRow++) {
    for(int bigCol = 0; bigCol < 3; bigCol++) {
        for(int smallCol = 0; smallCol < 3; smallCol++) {
            tic_tac_toe c = board.boards[bigRow][bigCol].cells[smallRow][smallCol]; 
            if(c == EMPTY) {
                printf("(%02d)", bigRow * 27 + bigCol * 9 + smallRow * 3 + smallCol + 1);
            } 
            else {  
                printf(" %c ", c == X ? 'X' : 'O');
            }
            
        }
        if(bigCol < 2) {
        printf("  |  ");
        }
    }
    printf("\n");
}
if(bigRow < 2) {
printf("--------------+----------------+--------------\n");
}
    }

}

