#include <stdio.h>
#include "board.h"

int main(void) {
    big_board bigBoard;
    init(&bigBoard);
    draw(bigBoard);
    return 0;
}