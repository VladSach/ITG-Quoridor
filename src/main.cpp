#include <iostream>
#include "Board.h"

#define watch(x) std::cout << #x << " is " << x << std::endl

int main() {
    Board game;
    game.initBoard();

    return 0;
}

