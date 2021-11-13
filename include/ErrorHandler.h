#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "Board.h"
#include "Player.h"
#include "utility.h"

#include <queue>
#include <stdexcept>

class ErrorHandler {
private:
    coordinates kludge = {1337, 1337};

public:
    void movePlayerErrorCheck(const coordinates &move, 
                              const coordinates &cur, 
                              const coordinates &other,
                              const Board &board);
                              
    bool checkPlayersEncounter(const coordinates &cur,
                               const coordinates &other);

    bool resolvePlayersEncounter(const coordinates &move, 
                                 const coordinates &cur, 
                                 const coordinates &other,
                                 const Board &board);

    void placeWallErrorCheck(const coordinates &move, Direction direction,
                             IPlayer &cur, const Board &board);
    int isPathExists(Board boardCopy, const int x, const int y, Direction direction);

    void addMove(std::vector<coordinates> &moves);
};

#endif // ERROR_HANDLER_H