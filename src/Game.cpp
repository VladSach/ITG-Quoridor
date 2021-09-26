#include "Game.h"

Game::Game() : firstPlayer(mapSize/2, mapSize-1, "John"),
               secondPlayer(mapSize/2, 0, "Bot") {

    board.initBoard();

    // Decides who acts first
    // ? Maybe do it random?
    currentPlayer = &firstPlayer;
}

void Game::switchCurrentPlayer() {
    (*currentPlayer == firstPlayer) ?
    currentPlayer = &secondPlayer :
    currentPlayer = &firstPlayer;
}

void Game::movePlayer(const int x, const int y) {
    // TODO: Add wall checking
    int curX, curY;
    currentPlayer->getPosition(&curX, &curY);
    
    int difX = curX - x;
    int difY = curY - y;

    if      (difY > 0) currentPlayer->movePlayer(up);
    else if (difY < 0) currentPlayer->movePlayer(down);
    else if (difX > 0) currentPlayer->movePlayer(right);
    else if (difX < 0) currentPlayer->movePlayer(left);

    switchCurrentPlayer();
}

void Game::placeWall(const int x, const int y, Direction direction) {
    // TODO: Add sanity check 
    switch (direction) {
    case horizontal:
        board.placeWall(x, y);
        board.placeWall(x+1, y);
        break;
    
    case vertical:
        board.placeWall(x, y);
        board.placeWall(x, y+1); 

    default:
        break;
    }

    currentPlayer->takeWall();
    switchCurrentPlayer();
}