#include <string.h>
#include <stdio.h>
#include "board.h"
#include <stdbool.h>
#include <stdlib.h>

//func for checking input for coin
char read_char(const char *prompt){
    char c;
    int ch;
    while(1){
        printf("%s", prompt);
        fflush(stdout); 
        c = getchar();
        if(c == EOF) exit(EXIT_FAILURE);
        while ((ch = getchar()) != '\n' && ch != EOF);
        if (c == 't' || c == 'T' || c == 'e' || c == 'E') return c;

        printf("INVALID INPUT\n");
    }
}

//func for receiving a integer for big board
size_t read_sz(void) {
  long input;
  size_t rc;
  while ((rc = scanf("%ld", &input)) != 1) {
    if(rc == EOF){
      exit(EXIT_FAILURE);
    }
    printf("INVALID: ");
    while (getchar() != '\n')
      ;  // clear buffer
  }
  while (getchar() != '\n')
    ;  // clear buffer
  return (size_t)input;
}

//func for asking yes or no for new game+
char read_yes_no(void){
    char c;
    int ch;
    while(1){
        c = getchar();
        if(c == EOF) exit(EXIT_FAILURE);
        while ((ch = getchar()) != '\n' && ch != EOF);
        if (c == 'y' || c == 'Y' || c == 'n' || c == 'N') return c;

        printf("INVALID INPUT\n");
    }

  } 

// telling to user about result of the game and asking   
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