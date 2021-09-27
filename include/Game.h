#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Observer.h"

#include <iostream>

class Game : public Observable {
private:
    Board board;

    Player firstPlayer;
    Player secondPlayer;
    Player *currentPlayer = nullptr;
    Player *winner = nullptr;

public:
    Game();
    ~Game() = default;

    void checkGameEnd();
    void switchCurrentPlayer();
    void movePlayer(const int x, const int y);
    void placeWall(const int x, const int y, Direction direction);

    Board getBoard();
    // ? No sure about that decision
    // ? Maybe get current player position?
    void getFirstPlayerPosition(int *x, int *y);
    void getSecondPlayerPosition(int *x, int *y);
};

#endif // GAME_H