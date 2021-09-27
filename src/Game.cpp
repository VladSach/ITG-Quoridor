#include "Game.h"

Game::Game() : firstPlayer(mapSize/2, mapSize-1, "John"),
               secondPlayer(mapSize/2, 0, "Bot") {

    board.initBoard();

    // ? Maybe do it random?
    // Decides who acts first
    currentPlayer = &firstPlayer;
}

void Game::switchCurrentPlayer() {
    (*currentPlayer == firstPlayer) ?
    currentPlayer = &secondPlayer :
    currentPlayer = &firstPlayer;
}

void Game::checkGameEnd() {
    int x1, y1, x2, y2;
    firstPlayer.getPosition(&x1, &y1);
    secondPlayer.getPosition(&x2, &y2);

    if (x1 == 0) winner = &firstPlayer;
    else if (x2 == mapSize - 1) winner = &secondPlayer;
    else winner = nullptr;
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
    checkGameEnd();
    notifyUpdate();
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
    checkGameEnd();
    notifyUpdate();
}

Board Game::getBoard() {
    return board;
}

void Game::getFirstPlayerPosition(int *x, int *y) {
    firstPlayer.getPosition(x, y);
}

void Game::getSecondPlayerPosition(int *x, int *y) {
    secondPlayer.getPosition(x, y);
}