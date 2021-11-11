#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Bot.h"
#include "Observer.h"
#include "utility.h"

#include <iostream>

#include <queue>
#include <stdexcept>

typedef std::pair<int, int> pair_ii;
typedef std::vector<std::pair<int, int>> vector_pair_ii;

class Game : public Observable {
private:
    Board board;

    IPlayer &firstPlayer;
    IPlayer &secondPlayer;
    IPlayer *currentPlayer = nullptr;
    IPlayer *winner = nullptr;

    vector_pair_ii possibleMoves;

public:
    Game(IPlayer &fp, IPlayer &sp);
    ~Game() = default;


    void initGame();
    bool checkGameEnd();
    void switchCurrentPlayer();
    void calculatePossibleMoves();
    std::vector<coordinates> calculateMeaningfulWalls(IPlayer &player);

    void decideTurn();
    void makeTurn(const int x, const int y);
    void movePlayer(const int x, const int y);
    void placeWall(const int x, const int y, Direction direction);
    
    bool checkPlayersEncounter();
    bool resolvePlayersEncounter(const int x, const int  y);

    void movePlayerErrorCheck(const int x, const int y);
    void placeWallErrorCheck(const int x, const int y, Direction direction);
    bool isPathExists(IPlayer &player, const int endRow, Board boardCopy,
                      const int x, const int y, Direction direction);

    // * View needed methods
    Board getBoard();
    std::vector<std::pair<int, int>> getPossibleMoves();

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
    pair_ii decideMovePosition();
    int minimax(coordinates &move, coordinates &action, int depth, bool maximizationPlayer, int alpha, int beta);
    
    int heuristic(coordinates &move);
    int heuristicMove();
    int heuristicWall();
};

#endif // GAME_H