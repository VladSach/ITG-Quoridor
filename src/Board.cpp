#include "Board.h"

void Board::initBoard() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            map[i][j].setPosition(i, j);
        }
    }
}