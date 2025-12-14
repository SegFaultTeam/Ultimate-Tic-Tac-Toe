#include <stdio.h>
#   include "board.h"
#include <stdbool.h>
#include "talking_with_user.h"
#include "play.h"

int main(void) {
    big_board bigBoard;
    bool game_over = false;
    bool first_move = true;
    char prompt[128];
    def_for_user gamer;
    while (!game_over){
        if(first_move){ //we throw a coin
            int coin = random(EAGLE, TAILS); 
            char c = read_char("Please choose (T)ails or (E)agle: ");
            if(coin == EAGLE && (c == 'e' || c == 'E')){
                printf("YOU CHOOSE EAGLE AND EAGLE DROPPED, YOU WIN COIN!!!!\n");
                gamer.user = player_1;
                gamer.symbol = X;
            }else if(coin == TAILS && (c == 't' || c == 'T')){
                printf("YOU CHOOSE TAILS AND TAILS DROPPED, YOU WIN COIN!!!!\n");
                gamer.user = player_1;
                gamer.symbol = X;
            }else{
                printf("Sorry, today isn't your day:(\n");
                gamer.user = player_2;
                gamer.symbol = O;
            }
            init(&bigBoard);
            draw(bigBoard);
        }
        first_move = false;
        if(gamer.user == player_1){
            if (bigBoard.next_col == -1 && bigBoard.next_row == -1) {
                snprintf(prompt, sizeof prompt, "You can place whenever you want, except already chosen position: ");
            } else {
                snprintf(prompt, sizeof prompt, "You can place just in [%ld][%ld], and just not taken cells: ", bigBoard.next_col, bigBoard.next_row);
            }           
            printf("%s", prompt); 
            while(!move_user(read_sz(), &bigBoard, gamer.symbol)){
                printf("We think your choise is incorrect, try again: ");
                printf("%s", prompt);
            }
            draw(bigBoard);
            check_win();
            if(check_full_win()){ // ask user to play again or break

            }
            computer_logic(&bigBoard, invert_symbol(gamer.symbol));
            draw(bigBoard);
            check_win();
            if(check_full_win()){ // ask user to play again or break
        }else{
            computer_logic(&bigBoard, invert_symbol(gamer.symbol));
            draw(bigBoard);
            check_win();
            if(check_full_win()){ // ask user to play again or break
            }
            if (bigBoard.next_col == -1 && bigBoard.next_row == -1) {
                snprintf(prompt, sizeof prompt, "You can place whenever you want, except already chosen position: ");
            } else {
                snprintf(prompt, sizeof prompt, "You can place just in [%ld][%ld], and just not taken cells: ", bigBoard.next_col, bigBoard.next_row);
            }           
            printf("%s", prompt); 
            while(!move_user(read_sz(), &bigBoard, gamer.symbol)){
                printf("We think your choise is incorrect, try again\n");
                printf("%s", prompt);
            }
            draw(bigBoard);
            check_win();
            if(check_full_win()){ // ask user to play again or break
            }
        }
    }
    return 0;
}
}