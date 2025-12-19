#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h> //for usleep func
#include <stdbool.h>
#define CYAN  "\033[0;36m"
#define RESET "\033[0m"
#define RED   "\033[0;031m"
#define BOLD_RED "\033[1;31m"
#define GREEN "\033[1;32m"

typedef enum{
    X,
    O,
    EMPTY,
    DRAW
}tic_tac_toe;

typedef enum{
    player_1,
    player_2
}players_turn;

typedef struct{
    players_turn user;
    tic_tac_toe symbol;
}def_for_user;

typedef struct{
    tic_tac_toe cells[3][3];
    tic_tac_toe winner;
}small_board;

typedef struct{
    small_board boards[3][3];
    players_turn current_player;
    int next_row, next_col;
}big_board;

big_board * init(void) { //initting board with EMPTY type
    big_board *bigBoard = malloc(sizeof(big_board));
    if(!bigBoard) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int bigRow = 0; bigRow < 3; bigRow++) {
        for(int bigCol = 0; bigCol < 3; bigCol++) {
            for(int smallRow = 0; smallRow < 3; smallRow++) {
                for(int smallCol = 0; smallCol < 3; smallCol++) {
                    bigBoard->boards[bigRow][bigCol].cells[smallRow][smallCol] = EMPTY;
                    bigBoard->boards[bigRow][bigCol].winner = EMPTY;
                }
            }
        }
    }
    bigBoard->next_col = -1;
    bigBoard->next_row = -1;
    return bigBoard;
}
void print_big_x(int row, bool userWinned) {
    if(row == 0) printf("%s", userWinned ? GREEN"   X     X  "RESET :BOLD_RED"   X     X  "RESET);
    if(row == 1) printf("%s", userWinned ? GREEN"      X     "RESET :BOLD_RED"      X     "RESET);
    if(row == 2) printf("%s", userWinned ? GREEN"   X     X  "RESET :BOLD_RED"   X     X  "RESET);
}
void print_big_o(int row, bool userWinned) {
    if(row == 0) printf("%s", userWinned ? GREEN"    OOOO    "RESET :BOLD_RED"    OOOO    "RESET);
    if(row == 1) printf("%s", userWinned ? GREEN"    O  O    "RESET :BOLD_RED"    O  O    "RESET);
    if(row == 2) printf("%s", userWinned ? GREEN"    OOOO    "RESET :BOLD_RED"    OOOO    "RESET);
}

void draw(big_board *board, tic_tac_toe user) { // console version of drawing func
    tic_tac_toe comp = user == O ? X  : O;
    int currentRow, currentCol;
    currentRow = board->next_row;
    currentCol = board->next_col;
    system("clear");
    for(int bigRow = 0; bigRow < 3; bigRow++) {
    for(int smallRow = 0; smallRow < 3; smallRow++) {
    for(int bigCol = 0; bigCol < 3; bigCol++) {
        if(board->boards[bigRow][bigCol].winner != EMPTY && board->boards[bigRow][bigCol].winner != DRAW) {
            bool userWinned = board->boards[bigRow][bigCol].winner == user ? true : false;
            board->boards[bigRow][bigCol].winner == X ? print_big_x(smallRow, userWinned) : print_big_o(smallRow, userWinned);
            
            
        } else {
        for(int smallCol = 0; smallCol < 3; smallCol++) {
            tic_tac_toe c = board->boards[bigRow][bigCol].cells[smallRow][smallCol]; 
            if(c == EMPTY) {
              if(currentRow == bigRow && currentCol == bigCol)  printf(RED"(%02d)"RESET, bigRow * 27 + bigCol * 9 + smallRow * 3 + smallCol + 1);
               else printf(CYAN"(%02d)"RESET, bigRow * 27 + bigCol * 9 + smallRow * 3 + smallCol + 1);
            }
            else {  
                if(currentRow == bigRow && currentCol == bigCol) {
                    printf(RED"%2s"RESET, c == X ? " X  " : " O  ");
                }
                else {
                printf(CYAN"%2s"RESET, c == X ? " X  " : " O  ");
                }
            }
            
        }
    }
        if(bigCol < 2) {
             printf(CYAN"  |  "RESET);   
        }
    }
    printf("\n");
}
if(bigRow < 2) {
    
printf(CYAN"--------------+----------------+--------------\n"RESET);
}
    }

}
tic_tac_toe invert_symbol(tic_tac_toe s) {
    if (s == X) return O;
    if (s == O) return X;
    else return EMPTY;
}

bool check_1_1(big_board *boards){
    if(boards->next_col == -1 && boards->next_row == -1){
        return true;
    }
    return false;
}

int next_col(big_board *boards){
    return boards->next_col;
}

int next_row(big_board *boards){
    return boards->next_row;
}

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
    if(board->boards[1][1].winner != EMPTY &&
       board->boards[1][1].winner != DRAW){
        if(board->boards[0][0].winner == board->boards[1][1].winner &&
           board->boards[1][1].winner == board->boards[2][2].winner)
            return board->boards[1][1].winner;
        else if(board->boards[0][2].winner == board->boards[1][1].winner &&
                board->boards[1][1].winner == board->boards[2][0].winner)
            return board->boards[1][1].winner;
    }
    for (int bigR = 0; bigR < 3; bigR++){
        if(board->boards[bigR][0].winner != EMPTY &&
           board->boards[bigR][0].winner != DRAW &&
           board->boards[bigR][0].winner == board->boards[bigR][1].winner &&
           board->boards[bigR][0].winner == board->boards[bigR][2].winner)
            return board->boards[bigR][0].winner;
    }
    for (int bigC = 0; bigC < 3; bigC++){
        if(board->boards[0][bigC].winner != EMPTY &&
           board->boards[0][bigC].winner != DRAW &&
           board->boards[0][bigC].winner == board->boards[1][bigC].winner &&
           board->boards[0][bigC].winner == board->boards[2][bigC].winner)
            return board->boards[0][bigC].winner;
    }
    return EMPTY;  
}


void check_for_avi(big_board *board){
    if(board->next_row == -1 && board->next_col == -1) return;
    if(board->boards[board->next_row][board->next_col].winner != EMPTY){
        board->next_row = -1;
        board->next_col = -1;
    }
}

bool cons_of_move_row(big_board * board, int row, int col, tic_tac_toe user) {
    size_t userCount = 0;
    for(int smallRow = 0; smallRow < 3; smallRow++) {
        for(int smallCol = 0; smallCol < 3; smallCol++) {
            if(board->boards[row][col].cells[smallRow][smallCol] == user) userCount++;
        }
    }
    if(userCount > 1) return false;
    return true;
}
bool cons_of_move_col(big_board * board, int row, int col, tic_tac_toe user) {
    size_t userCount = 0;
    for(int smallCol = 0; smallCol < 3; smallCol++) {
        for(int smallRow = 0; smallRow < 3; smallRow++) {
            if(board->boards[row][col].cells[smallRow][smallCol] == user) userCount++;
        }
    }
    if(userCount > 1) return false;
    return true;
} 
bool cons_of_move_diagonale(big_board * board, int row, int col, tic_tac_toe user) {
    int corners[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
    size_t userCount = 0;
    for(int i = 0; i < 4; i++) {
        int rows = corners[i][0];
        int cols = corners[i][1];
        if(board->boards[row][col].cells[rows][cols] == user) userCount++;
    }
    if(userCount > 1) return false;
    return true;
}
bool cons(big_board * board, int row, int col, tic_tac_toe user) {
    if(cons_of_move_col(board, row, col, user) && cons_of_move_row(board, row, col, user) && cons_of_move_diagonale(board, row, col, user)) return true;
    return false;
}
void absolute_fallback(big_board * board, tic_tac_toe comp) {
    for(int bigRows = 0; bigRows < 3; bigRows++) { //picking first non empty
            for(int bigCols = 0; bigCols < 3; bigCols++) {
                if(board->boards[bigRows][bigCols].winner != EMPTY) continue;
                for(int smallRows = 0; smallRows < 3; smallRows++) {
                    for(int smallCols = 0; smallCols < 3; smallCols++){
                        if(board->boards[bigRows][bigCols].cells[smallRows][smallCols] == EMPTY) {
                            board->boards[bigRows][bigCols].cells[smallRows][smallCols] = comp;
                            board->next_row = smallRows;
                            board->next_col = smallCols;
                            check_for_avi(board);
                            return;
                        }
                    }
                }
            }
            
        }
}
void fallback(big_board * board, tic_tac_toe comp) { 
    tic_tac_toe user = comp == O ? X : O;
    int corners[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
    if(board->next_col == -1 && board->next_row == -1) { //first case if computer is not limited
       
        if(board->boards[1][1].cells[1][1] == EMPTY && cons(board, 1, 1, user)) { //checking if center is empty
            board->boards[1][1].cells[1][1] = comp;
            board->next_col = 1;
            board->next_row = 1;
            return;
        }

        for(int i = 0; i<4; i++) { //checking for big corners
            int bigRows = corners[i][0];
            int bigCols = corners[i][1];
            if(board->boards[bigRows][bigCols].cells[1][1] == EMPTY && cons(board,1,1,user)) {
                board->boards[bigRows][bigCols].cells[1][1] = comp;
                board->next_col = 1;
                board->next_row = 1;
                return;
            }
        } 
        for(int bigRows = 0; bigRows < 3; bigRows++) { //checking for centers in small squares
            for(int bigCols = 0; bigCols < 3; bigCols++) {
                if(board->boards[bigRows][bigCols].cells[1][1] == EMPTY && cons(board, 1, 1, user)) {
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
                    if(board->boards[bigRows][bigCols].cells[rows][cols] == EMPTY && cons(board, rows , cols, user)) {
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
                if(board->boards[bigRows][bigCols].winner != EMPTY) continue;
                for(int smallRows = 0; smallRows < 3; smallRows++) {
                    for(int smallCols = 0; smallCols < 3; smallCols++){
                        if(board->boards[bigRows][bigCols].cells[smallRows][smallCols] == EMPTY && cons(board, smallRows, smallCols, user)) {
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
        if(board->boards[board->next_row][board->next_col].cells[1][1] == EMPTY && cons(board, 1, 1, user)) { //searching for center as second priority
            board->boards[board->next_row][board->next_col].cells[1][1] = comp;
            board->next_row = 1;
            board->next_col = 1;
            return;
        }
       
        for(int i = 0; i < 4; i++) { //searching for corners as third priority
            int rows = corners[i][0];
            int cols = corners[i][1];
            if(board->boards[board->next_row][board->next_col].cells[rows][cols] == EMPTY && cons(board, rows, cols, user)) {
                board->boards[board->next_row][board->next_col].cells[rows][cols] = comp;
                board->next_row = rows;
                board->next_col = cols;
                return;
            } 
        }
        for(int rows = 0 ; rows < 3; rows++) { //in other cases marking first non-empty place, but analyzing consequenses
            for(int cols = 0; cols < 3; cols++) {
                if(board->boards[board->next_row][board->next_col].cells[rows][cols] == EMPTY && cons(board, rows, cols, user)) {
                    board->boards[board->next_row][board->next_col].cells[rows][cols] = comp;
                    board->next_row = rows;
                    board->next_col = cols;
                    return;
                }
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

    absolute_fallback(board, comp);
}

void computer_logic(big_board *board, tic_tac_toe comp) {
    check_for_avi(board);
    tic_tac_toe user = comp == O ? X : O;

    if(board->next_col == -1 && board->next_row == -1) { //if computes is allowed to tick at any board
        for(int bigRow = 0; bigRow < 3; bigRow++) {
                for(int bigCol = 0; bigCol < 3; bigCol++) {
                    if(board->boards[bigRow][bigCol].winner != EMPTY) continue;
                    
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
}
//if there are none, calling fallback
            fallback(board, comp);
            return;
}


bool move_user(size_t n, big_board *boards, tic_tac_toe symbol_for_moving){
    if(n > 81 || n < 1) return false;
    n--;
    int big_r = n / 27;
    int big_c = (n / 9) % 3;
    int small_r = (n % 9) / 3;
    int small_c = n % 3;
    if(boards->boards[big_r][big_c].cells[small_r][small_c] != EMPTY) return false;
    if(boards->boards[big_r][big_c].winner != EMPTY) return false;
    if(boards->next_col == -1 && boards->next_row == -1){
        boards->boards[big_r][big_c].cells[small_r][small_c] = symbol_for_moving;
        boards->next_col = small_c;
        boards->next_row = small_r;
        return true;
    } else {
        if(big_r != boards->next_row || big_c != boards->next_col) return false;
        boards->boards[big_r][big_c].cells[small_r][small_c] = symbol_for_moving;
        boards->next_col = small_c;
        boards->next_row = small_r;
        return true;
    }
}

void free_board(big_board **board){
    free(*board);
    *board = NULL;
}