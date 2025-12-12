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