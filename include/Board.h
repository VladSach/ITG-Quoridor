#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Player.h"

enum {
    BoardSize = 9
};

enum PlayersChoice {
    placeWall = 0,
    changePosition
};

class Board {
private:
    Tile map[BoardSize][BoardSize]; 

    Player firstPlayer;
    Player secondPlayer;
    Player *currentPlayer;

public:
    Board() : firstPlayer(4, 0), 
              secondPlayer(4, 8) {};
    ~Board() = default;

    void initBoard();
    void playerMove(Player *currentPlayer, PlayersChoice choice);
    
};

#endif // BOARD_H
