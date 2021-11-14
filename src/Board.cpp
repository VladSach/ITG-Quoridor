#include "Board.h"

void Board::initBoard() {
    // Initiates clear board
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            //map[i][j] = (j % 2 == 0) ? tile : empty;
            if (i % 2 != 0) {
                map[i][j] = empty;
            } else if (j % 2 != 0) {
                map[i][j] = empty;
            } else {
                map[i][j] = tile;
            }
        }
    }
}

int Board::getTile(const int x, const int y) const{
    return map[y][x];
}

void Board::placeWall(const int x, const int y) {
    map[y][x] = wall;
}

void Board::freeWall(const int x, const int y) {
    if (x % 2 != 0 || y % 2 != 0) {
        map[y][x] = empty;
    }
}
