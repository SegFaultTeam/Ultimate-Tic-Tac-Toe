# Ultimate-Tic-Tac-Toe

## Game overview

This game is an improved version of the basic Tic-Tac-Toe. To win, a player must win three small boards in a row, column, or diagonal. The user plays against the computer, which has an approximately medium level of difficulty.
There are three possible outcomes: the user wins, the computer wins, or the game ends in a draw. After the game is finished, the user is asked whether they want to play another round.
The user can see the available board, which is highlighted in red. If the user wins a small board, it turns green and displays the user's symbol. If the computer wins, the board is shown in bold red with the computer's symbol.

## Design components

The following "entities" will be used to represent the game state (a high-level description is given first, followed by a more detailed description of each data structure in C code):

- `tic_tac_toe`: Represents a Tic-Tac-Toe cell. It can be X, O, EMPTY, or DRAW. The DRAW value is used only when a small board is fully completed and neither the user nor the computer has won.

- `players_turn`: Represents the current player’s turn. It can be either player_1 or player_2.

- `def_for_user`: Represents a user. A user has a symbol (tic_tac_toe enum) and a turn (players_turn enum).

- `small_board`: Represents a basic 3×3 board. It is filled with tic_tac_toe values (initially EMPTY) and also stores the winner of the board.

- `big_board`: Represents the main board in Ultimate Tic-Tac-Toe. It consists of a 3×3 grid of small_boards, tracks the current player, and stores the coordinates of the next available board (row, col).

### Data Structures and enumerations

#### tic_tac_toe

A tic_tac_toe enum is represented by the following structure:

```c
typedef enum{
    X,
    O,
    EMPTY,
    DRAW
}tic_tac_toe;
```

#### players_turn

A board is represented by the following structure:

```c
typedef enum{
    player_1,
    player_2
}players_turn;
```

#### def_for_user

```c
typedef struct{
    players_turn user;
    tic_tac_toe symbol;
}def_for_user;
```
The def_for_user structure stores whose turn it is and which symbol the user is playing with.

#### small_board

```c
typedef struct{
    tic_tac_toe cells[3][3];
    tic_tac_toe winner;
}small_board;

The small_board structure represents a 3×3 Tic-Tac-Toe board and stores the winner of that board.
```

#### big_board

```c
typedef struct{
    small_board boards[3][3];
    players_turn current_player;
    int next_row, next_col;
}big_board;
```
The big_board structure represents the main Ultimate Tic-Tac-Toe board. It contains a 3×3 grid of small_boards, tracks the current player, and stores the coordinates of the next required board.

## Interaction between components

At the highest level, the `main` function would look like this:

```c
int main(void) {
    while (game_not_finished) { //main loop
        if (first_move) {
            init_board(); //board initting
            toss_coin_and_set_player(); //choosing who will start the game
            first_move = false;
        }

        if (user_turn) { //if user starts
            get_user_move(); //user makes move
            apply_move(); //applying changes
            if (game_ended()) restart_or_exit(); //checking if game has ended
            computer_move(); //computer make a move
            if (game_ended()) restart_or_exit(); //checking again
        } else { //computer starts
            computer_move();   //computer makes a move 
            if (game_ended()) restart_or_exit(); //checking if game has ended
            get_user_move(); //user makes a move
            apply_move(); //applying changes
            if (game_ended()) restart_or_exit(); //checking if game has ended
        }
    }
    return 0;
}

```

The prototype of the function responsible for interacting with the user.

```c
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
```

## Header files

### talking_with_user.h

```c
char read_char(const char *prompt);
size_t read_sz(void);
char read_yes_no(void);
bool win_case(tic_tac_toe win_result, def_for_user player);
```

### board.h

```c
#ifndef BOARD_H
#define BOARD_H
#include <stdbool.h>
#include <stddef.h>
/* cell state */
typedef enum {
    X,
    O,
    EMPTY,
    DRAW
} tic_tac_toe;

/* player turn */
typedef enum {
    player_1,
    player_2
} players_turn;

typedef struct{
    players_turn user;
    tic_tac_toe symbol;
}def_for_user;

/* 3x3 board */
struct small_board;

/* ultimate board */
struct big_board;

/**
 * @brief Initialize ultimate tic-tac-toe board
 * @param board Pointer to big_board structure
 */
struct big_board *init(void);

/**
 * @brief Draw board to console
 * @param board Game board
 */
void draw(struct big_board *board, tic_tac_toe comp);
bool check_1_1(struct big_board *boards);
tic_tac_toe invert_symbol(tic_tac_toe s);
int next_row(struct big_board *boards);
int next_col(struct big_board *boards);
bool check_win(struct big_board *board);
tic_tac_toe check_full(const struct big_board *board);
bool move_user(size_t n, struct big_board *boards, tic_tac_toe symbol_for_moving);
void computer_logic(struct big_board *board, tic_tac_toe comp);
void check_for_avi(struct big_board *board);
void free_board(struct big_board *board);
#endif /* BOARD_H */
```
