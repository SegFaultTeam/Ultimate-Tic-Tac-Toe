#include <string.h>
#include <stdio.h>


char read_char(const char *prompt){
    char c;
    while(1){
        printf("%s", prompt);
        if(scanf("%c", &c) != 1){
            while(getchar() != '\n');
            printf("INVALID INPUT\n");
            continue;
        }
        if (c == 't' || c == 'T' || c == 'e' || c == 'E') return c;
        printf("INVALID INPUT\n");
        while (getchar() != '\n');
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