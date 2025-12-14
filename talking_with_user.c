#include <string.h>
#include <stdio.h>


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