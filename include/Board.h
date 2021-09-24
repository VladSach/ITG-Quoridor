#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Player.h"

class Board {
private:
    Tile map[9][9]; 
    // ??
    // int map[9][9]
    // unsigned char walls [9][9]
    Player firstPlayer; 
    Player secondPlayer;   

public:
    Board() : firstPlayer(4, 0), 
              secondPlayer(4, 8) {};
    ~Board() = default;

    void initBoard();
    

};

#endif // BOARD_H
