#ifndef BOARD_H
#define BOARD_H

#include "utility.h"

class Board {
private:

    int map[mapSize][mapSize]; 

public:
    Board() = default;
    ~Board() = default;

    void initBoard();
    int getTile(const int x, const int y) const;
    void placeWall(const int x, const int y);
    void freeWall(const int x, const int y);
};

#endif // BOARD_H
