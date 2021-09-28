#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Bot.h"
#include "Observer.h"

#include <iostream>

#include <queue>
#include <stdexcept>

class Game : public Observable {
private:
    Board board;

    IPlayer &firstPlayer;
    IPlayer &secondPlayer;
    IPlayer *currentPlayer = nullptr;
    IPlayer *winner = nullptr;

    std::vector<std::pair<int, int>> possibleMoves;

public:
    Game(IPlayer &fp, IPlayer &sp);
    ~Game() = default;

    void makeTurn(const int x, const int y);
    void calculatePossibleMoves();

    void initGame();
    bool checkGameEnd();
    void switchCurrentPlayer();

    void movePlayer(const int x, const int y);
    bool checkPlayersEncounter(const int x, const int y);
    void placeWall(const int x, const int y, Direction direction);

    void movePlayerErrorCheck(const int x, const int y);
    void placeWallErrorCheck(const int x, const int y, Direction direction);
    bool isPathExists(IPlayer &player, const int endRow, Board boardCopy,
                      const int x, const int y, Direction direction);

    // * View needed methods
    Board getBoard();
    std::vector<std::pair<int, int>> getPossibleMoves();

    bool getCurrentPlayerNeedsInput();
    void getFirstPlayerPosition(int *x, int *y);
    void getSecondPlayerPosition(int *x, int *y);

    const char *getFirstPlayerName();
    const char *getSecondPlayerName();
    const char *getCurrentPlayerName();
    const char *getWinnerName();
};

#endif // GAME_H