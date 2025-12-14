#include <stdio.h>
#include "board.h"
#include <stdbool.h>
#include "talking_with_user.h"
#include "play.h"

int main(void) {
    big_board bigBoard;
    init(&bigBoard);
    draw(bigBoard);
    bool game_over = false;
    bool first_move = true;
    def_for_user gamer;
    while (!game_over){
        if(first_move){ //we throw a coin
            int coin = random(EAGLE, TAILS); 
            char c = read_char("Please choose (T)ails or (E)agle: ");
            if(coin == EAGLE && (c == 'e' || c == 'E')){
                gamer.user = player_1;
                gamer.symbol = X;
            }else if(coin == TAILS && (c == 't' || c == 'T')){
                gamer.user = player_1;
                gamer.symbol = X;
            }else{
                gamer.user = player_2;
                gamer.symbol = O;
            }
        }
        first_move = false;
        if(gamer.user == player_1){
            while(!move_user(read_sz(), &bigBoard, gamer.symbol)){
                ;
            }
            chech_win();
            check_full_win();
            if(c)
        }
    }
    return 0;
}