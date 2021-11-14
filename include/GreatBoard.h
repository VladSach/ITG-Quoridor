#ifndef GREAT_BOARD_H
#define GREAT_BOARD_H

#include "Board.h"
#include "Player.h"
#include "ErrorHandler.h"

#include <vector>

// Class handles player-map interactions
class GreatBoard {
public:
    bool movePlayer(const int x, const int y, 
                   IPlayer &player, Board &board,
                   std::vector<coordinates> moves);
    void placeWall(const int x, const int y, Direction direction, 
                   IPlayer &player, Board &board);
    void freeWall(const int x, const int y, Direction direction, 
                  IPlayer &player, Board &board);

    std::vector<coordinates> calculatePossibleMoves(const coordinates &cur,
                                                    const coordinates &other,
                                                    Board &board);

    std::vector<coordinates> calculateMeaningfulWalls(IPlayer &cur,
                                                      IPlayer &other,
                                                      Board board,
                                                      const int r);

    coordinates decideMove();
};

#endif // GREAT_BOARD_H 