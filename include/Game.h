#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Bot.h"
#include "Observer.h"
#include "ErrorHandler.h"
#include "GreatBoard.h"
#include "utility.h"

#include <iostream>

// TODO: One day rename board to map and greatBoard to board
class Game : public Observable {
private:
    Board board;
    GreatBoard greatBoard;
    ErrorHandler checker;

    IPlayer &firstPlayer;
    IPlayer &secondPlayer;
    IPlayer *currentPlayer = nullptr;
    IPlayer *otherPlayer = nullptr;
    IPlayer *winner = nullptr;

    std::vector<coordinates> possibleMoves;

public:
    Game(IPlayer &fp, IPlayer &sp);
    ~Game() = default;

    void initGame();
    bool checkGameEnd();
    void switchCurrentPlayer();
    
    std::vector<coordinates> calculateMeaningfulWalls(IPlayer &player);

    void decideTurn();
    void makeTurn(const int x, const int y);
    void movePlayer(const int x, const int y);
    void placeWall(const int x, const int y);
    
    void updatePossibleMoves();

    // * Getters
    Board getBoard();
    std::vector<coordinates> getPossibleMoves();

    bool getCurrentPlayerNeedsInput();

    coordinates getFirstPlayerPosition();
    coordinates getSecondPlayerPosition();
    coordinates getCurrentPlayerPosition();
    coordinates getOtherPlayerPosition();

    int getFirstPlayerWalls();
    int getSecondPlayerWalls();

    const char *getFirstPlayerName();
    const char *getSecondPlayerName();
    const char *getCurrentPlayerName();
    const char *getWinnerName();

    // Minimax algo
    // TODO: separate class
    coordinates decideMovePosition();
    int minimax(coordinates &move, coordinates &action, int depth, bool maximizationPlayer, int alpha, int beta);
    
    int shortestPathToRow(IPlayer &player, const int endRow);

    int heuristic(coordinates &move);
    int heuristicMove();
    int heuristicWall();
};

#endif // GAME_H