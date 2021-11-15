#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "Board.h"
#include "Player.h"
#include "utility.h"

#include <queue>
#include <stdexcept>

class ErrorHandler {
protected:
    ErrorHandler(){ }

    static ErrorHandler* singleton_;

private:
    std::vector<coordinates> kludge;

public:
    ErrorHandler(ErrorHandler &other) = delete;
    void operator=(const ErrorHandler &) = delete;
    static ErrorHandler *GetInstance();

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
                             IPlayer &cur, IPlayer &other, const Board &board);
    bool isPathExists(IPlayer &player, Board boardCopy, 
                      const int x, const int y, Direction direction);

    void addMove(std::vector<coordinates> &moves);
};

#endif // ERROR_HANDLER_H