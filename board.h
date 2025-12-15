#ifndef BOARD_H
#define BOARD_H
#include <stdbool.h>
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
void draw(struct big_board *board);
bool check_1_1(struct big_board *boards);
tic_tac_toe invert_symbol(tic_tac_toe s);
#endif /* BOARD_H */