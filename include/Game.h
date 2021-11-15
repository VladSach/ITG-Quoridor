#ifndef GAME_H
#define GAME_H

#include "Bot.h"
#include "Board.h"
#include "Player.h"
#include "utility.h"
#include "Observer.h"
#include "GreatBoard.h"
#include "MoveChooser.h"
#include "ErrorHandler.h"

// TODO: One day rename board to map and greatBoard to board
class Game : public Observable {
private:
    Board board;
    GreatBoard greatBoard;
    MoveChooser chooser;

    coordinates lastMove;

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
    
    void decideTurn();
    void makeTurn(const int x, const int y);
    void movePlayer(const int x, const int y);
    void placeWall(const int x, const int y);
    
    void updatePossibleMoves();

    // * Getters
    Board getBoard();
    std::vector<coordinates> getPossibleMoves();
    coordinates getLastMove();

    bool getCurrentPlayerNeedsInput();

    int getFirstPlayerWalls();
    int getSecondPlayerWalls();

    coordinates getFirstPlayerPosition();
    coordinates getSecondPlayerPosition();
    coordinates getCurrentPlayerPosition();
    coordinates getOtherPlayerPosition();

    const char *getFirstPlayerName();
    const char *getSecondPlayerName();
    const char *getCurrentPlayerName();
    const char *getWinnerName();
};

#endif // GAME_H