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

// Calculates possible moves directions for chosen player
// ! Didn't come up with clever way to get rid of checker here
std::vector<coordinates> GreatBoard::calculatePossibleMoves(const coordinates &cur,
                                                            const coordinates &other,
                                                            Board &board, 
                                                            ErrorHandler checker) {

    int r = 2; // * radius
    std::vector<coordinates> possibleMoves;

    if(checker.checkPlayersEncounter(cur, other)) r = 4;

    for(int x = cur.x - r; x <= cur.x + r; x+=2) {
        for (int y = cur.y - r; y <= cur.y + r; y+=2) {
            try {
                checker.movePlayerErrorCheck(coordinates {x, y}, cur,
                                             other, board);
            } catch(const std::exception& e) {
                continue;
            }

            checker.addMove(possibleMoves);
            possibleMoves.push_back(coordinates {x, y});
        }
    }

    return possibleMoves;
}

