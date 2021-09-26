#ifndef BOARD_H
#define BOARD_H

#include "Player.h"

enum Field {
    empty = 0,
    tile  = 1,
    wall  = 2
};

enum PlayersChoice {
    placeWall = 0,
    changePosition
};

enum Walls { 
    leftWall  = 0x01,  // 0000 0001 
    upperWall = 0x02,  // 0000 0010
    lowerWall = 0x04,  // 0000 0100
    rightWall = 0x08,  // 0000 1000
    //lowMask = 0xFF // bitmask for storing last 4 bits
};

class Board {
private:
    char **map; 
    const int m_mapSize = 17;

    // m_walls is a bitset
    unsigned char m_walls = 0x0; // 1 byte

    Player firstPlayer;
    Player secondPlayer;
    Player *currentPlayer;

public:
    Board() : firstPlayer(4, 0), 
              secondPlayer(4, 8) {};
    ~Board() = default;

    void initBoard();
    void setWall(unsigned char wall);
    void playerMove(Player *currentPlayer, PlayersChoice choice);
    
};

#endif // BOARD_H
