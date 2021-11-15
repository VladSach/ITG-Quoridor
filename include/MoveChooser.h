#ifndef MOVE_CHOOSER_H
#define MOVE_CHOOSER_H

#include "Bot.h"
#include "Board.h"
#include "Player.h"
#include "utility.h"
#include "GreatBoard.h"
#include "ErrorHandler.h"

#include <iostream>

class MoveChooser {
private:
    Board board;
    GreatBoard gb;

    Bot bot;
    Player player;

public:
    bool checkWinCondition();

    coordinates decideMove(Board board, GreatBoard &gb, Bot bot, Player player);
    int minimax(coordinates &move, 
                coordinates &best, 
                int depth, bool maximizingPlayer, 
                int alpha, int beta);
    int heuristic(coordinates &move, bool maximizingPlayer);

    int shortestPathToRow(IPlayer &player, const int endCol);

    // * Mock functions *
    void makeTurn(const int x, const int y, IPlayer &player, std::vector<coordinates> moves);
    void placeWall(const int x, const int y, IPlayer &player);
    void freeWall(const int x, const int y, IPlayer &player);
};

#endif // MOVE_CHOOSER_H