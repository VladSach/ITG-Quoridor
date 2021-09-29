#ifndef BOARD_H
#define BOARD_H

enum {
    mapSize = 17
};

enum Field {
    empty = 0,
    tile  = 1,
    wall  = 2
};

enum Direction {
    horizontal = 0,
    vertical
};

class Board {
private:

    int map[mapSize][mapSize]; 

public:
    Board() = default;
    ~Board() = default;

    void initBoard();
    int getTile(const int x, const int y);
    void placeWall(const int x, const int y);
};

#endif // BOARD_H
