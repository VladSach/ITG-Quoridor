#include "Game.h"

Game::Game() : firstPlayer(mapSize/2, 10, "John"),
               secondPlayer(mapSize/2, 12, "Bot") {

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

bool Game::checkGameEnd() {
    int x1, y1, x2, y2;
    firstPlayer.getPosition(&x1, &y1);
    secondPlayer.getPosition(&x2, &y2);

    if (y1 == 0) {
        winner = &firstPlayer;
        return true;
    } else if (y2 == mapSize - 1) {
        winner = &secondPlayer;
        return false;
    } else {
        winner = nullptr;
        return false;
    }
}

void Game::movePlayer(const int x, const int y) {
    movePlayerErrorCheck(x, y);

    if (checkPlayersEncounter(x, y)) return;

    int curX, curY;
    currentPlayer->getPosition(&curX, &curY);
    
    const int difX = x - curX;
    const int difY = curY - y;

    if      (difY > 0) currentPlayer->movePlayer(up);
    else if (difY < 0) currentPlayer->movePlayer(down);
    else if (difX > 0) currentPlayer->movePlayer(right);
    else if (difX < 0) currentPlayer->movePlayer(left);

    switchCurrentPlayer();
    checkGameEnd();
    notifyUpdate();
}

// * Checks if players in front of each other and solves it
bool Game::checkPlayersEncounter(const int x, const int y){
    // ! God, this is awful
    int curX, curY, otherX, otherY;
    currentPlayer->getPosition(&curX, &curY);
    switchCurrentPlayer();
    currentPlayer->getPosition(&otherX, &otherY);
    switchCurrentPlayer();

    // P for players
    const int difPX = curX - otherX;
    const int difPY = curY - otherY;
    
    // Are players near each other
    if (difPX > 2 || difPY > 2) return false;

    const int difX = x - curX;
    const int difY = curY - y; 
    
    // * No need for cmath library and abs()
    // * http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
    const int maskX = difX >> (sizeof(int) * __CHAR_BIT__ - 1);
    const int maskY = difY >> (sizeof(int) * __CHAR_BIT__ - 1);
    unsigned int difXAbs = (difX + maskX) ^ maskX;
    unsigned int difYAbs = (difY + maskY) ^ maskY;

    // Are player wants to overstep another
    if (!(difX == 0 && difYAbs == 4) || 
        !(difY == 0 && difXAbs == 4)) {
            return false;
        }

    // TODO: if there is a wall

    if      (difY > 0) currentPlayer->doubleMove(up);
    else if (difY < 0) currentPlayer->doubleMove(down);
    else if (difX > 0) currentPlayer->doubleMove(right);
    else if (difX < 0) currentPlayer->doubleMove(left);

    switchCurrentPlayer();
    checkGameEnd();
    notifyUpdate();
            
    return true;
}

void Game::placeWall(const int x, const int y, Direction direction) {
    placeWallErrorCheck(x, y, direction);

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

const char *Game::getFirstPlayerName() {
    return firstPlayer.getName();
}

const char *Game::getSecondPlayerName() {
    return secondPlayer.getName();
}

const char *Game::getCurrentPlayerName() {
    return currentPlayer->getName();
}

const char *Game::getWinnerName() {
    return winner->getName();
}

void Game::movePlayerErrorCheck(const int x, const int y) {
    // Out of bounds
    if (x > 17 || y > 17 || x < 0 || y < 0) {
        throw std::invalid_argument(
            "Oof, someone's trying to escape\nNot gonna happen"
        );
    }

    // Wall on the path
    int curX, curY;
    currentPlayer->getPosition(&curX, &curY);
    
    int difX = x - curX;
    int difY = curY - y;

    if (difY > 0) {
        if (board.getTile(curX, curY-1) == wall) {
            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    }
    else if (difY < 0) {
        if (board.getTile(curX, curY+1) == wall) {
            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    }
    else if (difX > 0) {
        if (board.getTile(curX+1, curY) == wall) {
            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    }
    else if (difX < 0) {
        if (board.getTile(curX-1, curY) == wall) {
            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    }
}

void Game::placeWallErrorCheck(const int x, const int y, Direction direction) {
    // Place wall on wall or wall on tile
    switch (direction) {
    case horizontal:
        if(board.getTile(x, y) == wall || 
           board.getTile(x+1, y) == wall) { 
                throw std::invalid_argument(
                    "Hey, there's already a wall"
                );
        }

        if (board.getTile(x, y) == tile ||
            board.getTile(x+1, y) == tile) {
                throw std::invalid_argument(
                    "You can't build a wall here, we walk on this"
                );
            }

        break;

    case vertical:
        if(board.getTile(x, y) == wall || 
           board.getTile(x, y+1) == wall) {
                throw std::invalid_argument(
                    "Hey, there's already a wall"
                );
        }

        if (board.getTile(x, y) == tile ||
            board.getTile(x, y+1) == tile) {
                throw std::invalid_argument(
                    "You can't build a wall here, we walk on this"
                );
            }

        break;

    default:
        break;
    }

    // TODO: Add last path blocked 
    // Player has no walls
    if (currentPlayer->getWallsCounter() == 0) {
        throw std::invalid_argument(
            "Sorry, Pal, looks like you're short on walls"
        );
    }

    // Closes last path to finish
}