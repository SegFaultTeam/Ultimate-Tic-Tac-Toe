/* cell state */
typedef enum {
    X,
    O,
    EMPTY
} tic_tac_toe;

/* player turn */
typedef enum {
    player_1,
    player_2
} players_turn;

/* 3x3 board */
typedef struct {
    tic_tac_toe cells[3][3];
    tic_tac_toe winner;
} small_board;

/* ultimate board */
typedef struct {
    small_board boards[3][3];
    players_turn current_player;
    size_t next_row;
    size_t next_col;
} big_board;

/**
 * @brief Initialize ultimate tic-tac-toe board
 * @param board Pointer to big_board structure
 */
void init(big_board *board);

/**
 * @brief Draw board to console
 * @param board Game board
 */
void draw(big_board board);