typedef enum{
    EAGLE,
    TAILS
}coin;

static void seed_prng(void);
int randkom(int minimum, int maxaimum);
bool move_user(size_t n, struct big_board *boards, tic_tac_toe symbol_for_moving);
void computer_logic(struct big_board *board, tic_tac_toe comp);