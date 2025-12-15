#include <stdio.h>
#include "board.h"
#include <stdbool.h>
#include "talking_with_user.h"
#include <unistd.h>
#include "play.h"

int main(void) {
    struct big_board *bigBoard = NULL;
    size_t count_wins;
    bool game_over = false;
    bool first_move = true;
    char prompt[128];
    def_for_user gamer;
    
    while (!game_over){
        if(first_move){ 
            bigBoard = init();
            int coin = randkom(0, 1); 
            char c = read_char("Please choose (T)ails or (E)agle: ");
            if(coin == 0 && (c == 'e' || c == 'E')){
                printf("YOU CHOOSE EAGLE AND EAGLE DROPPED, YOU WIN COIN!!!!\n");
                gamer.user = player_1;
                gamer.symbol = X;
            }else if(coin == 1 && (c == 't' || c == 'T')){
                printf("YOU CHOOSE TAILS AND TAILS DROPPED, YOU WIN COIN!!!!\n");
                gamer.user = player_1;
                gamer.symbol = X;
            }else{
                printf("Sorry, today isn't your day:(\n");
                gamer.user = player_2;
                gamer.symbol = O;
            }
            count_wins = 0;
            usleep(5000000);
            draw(bigBoard);
        }
        first_move = false;
        
        if(gamer.user == player_1){
            if (check_1_1(bigBoard)) {
                snprintf(prompt, sizeof prompt, "You can place whenever you want, except already chosen position: ");
            } else {
                snprintf(prompt, sizeof prompt, "You can place just in [%d][%d], and just not taken cells: ", next_row(bigBoard), next_col(bigBoard));
            }           
            printf("%s", prompt); 
            while(!move_user(read_sz(), bigBoard, gamer.symbol)){
                printf("We think your choise is incorrect, try again: ");
                printf("%s", prompt);
            }
            check_for_avi(bigBoard);
            draw(bigBoard);
            
            if(check_win(bigBoard)){
                count_wins++;
                if(check_full(bigBoard) != EMPTY) return 52;
                if(count_wins == 9) return 333939;
            }
            draw(bigBoard);
            usleep(2000000);
            computer_logic(bigBoard, invert_symbol(gamer.symbol));
            check_for_avi(bigBoard);
            draw(bigBoard);
            
            if(check_win(bigBoard)){
                count_wins++;
                tic_tac_toe win_var = check_full(bigBoard);
                if(win_var != EMPTY) {
                    if(win_case(win_var, gamer)){
                        first_move = true;
                        continue;
                    }else{
                        printf("BYE\n");
                        return 42;
                    }
                }
                if(count_wins == 9) {
                    if(win_case(DRAW, gamer)){
                        first_move = true;
                        continue;
                    }else{
                        printf("BYE\n");
                        return 42;
                    }
                }
            }
            
        }else{
            usleep(2000000);
            computer_logic(bigBoard, invert_symbol(gamer.symbol));
            check_for_avi(bigBoard);
            draw(bigBoard);
            
            if(check_win(bigBoard)){
                count_wins++;
                tic_tac_toe win_var = check_full(bigBoard);
                if(win_var != EMPTY) {
                    if(win_case(win_var, gamer)){
                        first_move = true;
                        continue;
                    }else{
                        printf("BYE\n");
                        return 42;
                    }
                }
                if(count_wins == 9) {
                    if(win_case(DRAW, gamer)){
                        first_move = true;
                        continue;
                    }else{
                        printf("BYE\n");
                        return 42;
                    }
                }
            }
            
            // ХОД ИГРОКА
            if (check_1_1(bigBoard)) {
                snprintf(prompt, sizeof prompt, "You can place whenever you want, except already chosen position: ");
            } else {
                snprintf(prompt, sizeof prompt, "You can place just in [%d][%d], and just not taken cells: ", next_row(bigBoard), next_col(bigBoard));
            }           
            printf("%s", prompt); 
            while(!move_user(read_sz(), bigBoard, gamer.symbol)){
                printf("We think your choise is incorrect, try again\n");
                printf("%s", prompt);
            }
            check_for_avi(bigBoard);
            draw(bigBoard);
            
            if(check_win(bigBoard)){
                count_wins++;
                tic_tac_toe win_var = check_full(bigBoard);
                if(win_var != EMPTY) {
                    if(win_case(win_var, gamer)){
                        first_move = true;
                        continue;
                    }else{
                        printf("BYE\n");
                        return 42;
                    }
                }
                if(count_wins == 9) {
                    if(win_case(DRAW, gamer)){
                        first_move = true;
                        continue;
                    }else{
                        printf("BYE\n");
                        return 42;
                    }
                }
            }
        }
    }
    return 0;
}