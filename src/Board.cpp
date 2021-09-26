#include "Board.h"

void Board::initBoard() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            map[i][j].setPosition(i, j);
        }
    }

    // TODO: do this in a random way
    currentPlayer = &firstPlayer;

}

void Board::playerMove(Player *currentPlayer, PlayersChoice choice) {
    switch (choice) {
    case placeWall:
        currentPlayer->takeWall();
        break;

    case changePosition:

        break;
    
    default:
        break;
    }
}