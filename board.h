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
void draw(struct big_board *board);
bool check_1_1(struct big_board *boards);
tic_tac_toe invert_symbol(tic_tac_toe s);
int next_row(struct big_board *boards);
int next_col(struct big_board *boards);
bool check_win(struct big_board *board);
tic_tac_toe check_full(const struct big_board *board);
bool move_user(size_t n, struct big_board *boards, tic_tac_toe symbol_for_moving);
void computer_logic(struct big_board *board, tic_tac_toe comp);
void check_for_avi(struct big_board *board);
#endif /* BOARD_H */