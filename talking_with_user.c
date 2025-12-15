#include <string.h>
#include <stdio.h>
#include "board.h"
#include <stdbool.h>

char read_char(const char *prompt){
    char c;
    int ch;
    while(1){
        printf("%s", prompt);
        fflush(stdout); 
        c = getchar();
        while ((ch = getchar()) != '\n' && ch != EOF);
        if (c == 't' || c == 'T' || c == 'e' || c == 'E') return c;

        printf("INVALID INPUT\n");
    }
}


size_t read_sz(void) {
  long input;
  while (scanf("%ld", &input) != 1) {
    printf("INVALID: ");
    while (getchar() != '\n')
      ;  // clear buffer
  }
  while (getchar() != '\n')
    ;  // clear buffer
  return (size_t)input;
}

char read_yes_no(void){
    char c;
    int ch;
    while(1){
        printf("%s", prompt);
        fflush(stdout); 
        c = getchar();
        while ((ch = getchar()) != '\n' && ch != EOF);
        if (c == 'y' || c == 'Y' || c == 'n' || c == 'N') return c;

        printf("INVALID INPUT\n");
    }

  } 
bool win_case(tic_tac_toe win_result, def_for_user player){
    if(win_result == DRAW){
        printf("IT'S A DRAW, GOOD GAME, WANT TO TRY AGAIN(y/n): ");
        char c = read_yes_no();
        if(strrchr("Yy", c)) return true;
        else return false;
    }else if(win_result == player.symbol){
      printf("YOU WIN!!! YOU ARE REALLY GOOD, GOOD GAME, WANT TO TRY AGAIN(y/n): ");
        char c = read_yes_no();
        if(strrchr("Yy", c)) return true;
        else return false;
    }else{
      printf("Sorry, you lose:(, want to try again?(y/n): ");
        char c = read_yes_no();
        if(strrchr("Yy", c)) return true;
        else return false;
    }
}