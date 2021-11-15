#include "Game.h"

Game::Game(IPlayer &fp, IPlayer &sp) : 
           firstPlayer(fp), secondPlayer(sp) { }

void Game::initGame() {
    board.initBoard();

    // Decides who acts first
    currentPlayer = &firstPlayer;
    otherPlayer = &secondPlayer;
    updatePossibleMoves();

    notifyUpdate();
}

void Game::switchCurrentPlayer() {
    if (*currentPlayer == firstPlayer) {
        currentPlayer = &secondPlayer;
        otherPlayer = &firstPlayer;
    } else {
        currentPlayer = &firstPlayer;
        otherPlayer = &secondPlayer;
    }
}

bool Game::checkGameEnd() {
    coordinates coordF, coordS;
    coordF = getFirstPlayerPosition();
    coordS = getSecondPlayerPosition();

    if (coordF.y == 0) {
        winner = &firstPlayer;
        return true;
    } else if (coordS.y == mapSize - 1) {
        winner = &secondPlayer;
        return true;
    } else {
        winner = nullptr;
        return false;
    }
}

void Game::decideTurn() {
    coordinates move;
    
    move = chooser.decideMove(board, greatBoard,
                              static_cast<Bot&>(*currentPlayer),
                              static_cast<Player&>(*otherPlayer));

    makeTurn(move.x, move.y);

    
}

void Game::makeTurn(const int x, const int y) {

    // * Build a wall or move
    if (x % 2 != 0 || y % 2 != 0) {
        placeWall(x, y);
    } else {
        movePlayer(x, y);
    }

    lastMove = {x, y};

    switchCurrentPlayer();
    updatePossibleMoves();
    checkGameEnd();
    notifyUpdate();
}

void Game::movePlayer(const int x, const int y) {
    bool isOk = greatBoard.movePlayer(x, y, *currentPlayer, board, possibleMoves);

    ErrorHandler* checker = ErrorHandler::GetInstance();

    // * Returns player a message why his move is wrong
    // ! Using exceptions to do this is actually a terrible idea
    // ! But it's a pain to rewrite whole error system, so I won't do it
    if (!isOk) {
        checker->movePlayerErrorCheck(coordinates {x, y},
                                     getCurrentPlayerPosition(),
                                     getOtherPlayerPosition(),
                                     board);
    }
}

void Game::placeWall(const int x, const int y) {
    ErrorHandler* checker = ErrorHandler::GetInstance();

    if (x % 2 == 0 && y % 2 != 0) {
        checker->placeWallErrorCheck(coordinates {x, y}, horizontal, *currentPlayer, *otherPlayer, board);
        greatBoard.placeWall(x, y, horizontal, *currentPlayer, board);
    } else if (x % 2 != 0 && y % 2 == 0) {
        checker->placeWallErrorCheck(coordinates {x, y}, vertical, *currentPlayer, *otherPlayer, board);
        greatBoard.placeWall(x, y, vertical, *currentPlayer, board);
    }
}

void Game::updatePossibleMoves() {
    possibleMoves = greatBoard.calculatePossibleMoves(getCurrentPlayerPosition(),
                                                      getOtherPlayerPosition(),
                                                      board);
}

// * -------------------------------------------------- *
// *                    Getters                         *
// * -------------------------------------------------- *

Board Game::getBoard() {
    return board;
}

std::vector<coordinates> Game::getPossibleMoves() {
    return possibleMoves;
}

coordinates Game::getLastMove() {
    return lastMove;
}

bool Game::getCurrentPlayerNeedsInput() {
    return currentPlayer->needsToTakeInput();
}

coordinates Game::getFirstPlayerPosition() {
    return firstPlayer.getPosition();
}

coordinates Game::getSecondPlayerPosition() {
    return secondPlayer.getPosition();
}

coordinates Game::getCurrentPlayerPosition() {
    return currentPlayer->getPosition();
}

coordinates Game::getOtherPlayerPosition() {
    return otherPlayer->getPosition();
}

int Game::getFirstPlayerWalls() {
    return firstPlayer.getWallsCounter();
}

int Game::getSecondPlayerWalls() {
    return secondPlayer.getWallsCounter();
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