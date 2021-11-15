#include "GreatBoard.h"

bool GreatBoard::movePlayer(const int x, const int y, 
                            IPlayer &player, Board &board,
                            std::vector<coordinates> moves) {
    bool found = false;

    if (player.needsToTakeInput()) {
        for (auto e : moves) {
            if (e.x == x && e.y == y) {
                found = true;
            }
        }

        if (!found) { return false; }
    }

    player.move(x, y);
    return true;
}

void GreatBoard::placeWall(const int x, const int y, Direction direction, 
                           IPlayer &player, Board &board) {

    switch (direction) {
    case horizontal:
        board.placeWall(x, y);
        board.placeWall(x+1, y);
        board.placeWall(x+2, y);
        break;
    
    case vertical:
        board.placeWall(x, y);
        board.placeWall(x, y+1);
        board.placeWall(x, y+2);
        break;

    default:
        break;
    }

    player.reduceWall();
}

void GreatBoard::freeWall(const int x, const int y, Direction direction, 
                          IPlayer &player, Board &board) {

    switch (direction) {
    case horizontal:
        board.freeWall(x, y);
        board.freeWall(x+1, y);
        board.freeWall(x+2, y);
        break;
    
    case vertical:
        board.freeWall(x, y);
        board.freeWall(x, y+1);
        board.freeWall(x, y+2);
        break;

    default:
        break;
    }

    player.returnWall();
}

// Calculates possible moves directions for chosen player
// ! Didn't come up with clever way to get rid of checker here
std::vector<coordinates> GreatBoard::calculatePossibleMoves(const coordinates &cur,
                                                            const coordinates &other,
                                                            Board &board) {

    int r = 2; // * radius
    std::vector<coordinates> possibleMoves;
    ErrorHandler* checker = ErrorHandler::GetInstance();

    if(checker->checkPlayersEncounter(cur, other)) r = 4;

    for(int x = cur.x - r; x <= cur.x + r; x+=2) {
        for (int y = cur.y - r; y <= cur.y + r; y+=2) {
            try {
                checker->movePlayerErrorCheck(coordinates {x, y}, cur,
                                             other, board);
            } catch(const std::exception& e) {
                checker->addMove(possibleMoves);
                continue;
            }

            checker->addMove(possibleMoves);
            possibleMoves.push_back(coordinates {x, y});
        }
    }

    return possibleMoves;
}

// Looks for wall around player
// @param r Radius from player to walls
std::vector<coordinates> GreatBoard::calculateMeaningfulWalls(IPlayer &cur,
                                                              IPlayer &other,
                                                              Board board,
                                                              const int r = 2) {
    // Possible walls location
    // (x-2 y-1), (x y-1), (x-2 y+1), (x y+1)
    // (y-2 x-1), (y x-1), (y-2 x+1), (y x+1)

    coordinates coordP;
    coordP = cur.getPosition();

    std::vector<coordinates> walls;

    ErrorHandler* checker = ErrorHandler::GetInstance();

    for(int x = coordP.x - r; x <= coordP.x; x+=2) {
        for (int y = coordP.y - 1; y <= coordP.y + 1; y+=2) {
            try {
                checker->placeWallErrorCheck(coordinates {x, y}, horizontal, cur, other, board);
            } catch(const std::exception& e) {
                continue;
            }

            walls.push_back(coordinates{x, y});
        }
    }

    for(int y = coordP.y - r; y <= coordP.y; y+=2) {
        for (int x = coordP.x - 1; x <= coordP.x + 1; x+=2) {
            try {
                checker->placeWallErrorCheck(coordinates {x, y}, vertical, cur, other, board);
            } catch(const std::exception& e) {
                continue;
            }

            walls.push_back(coordinates{x, y});
        }
    }

    return walls;
}