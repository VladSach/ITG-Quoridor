#include "Game.h"

Game::Game(IPlayer &fp, IPlayer &sp) : 
           firstPlayer(fp), secondPlayer(sp) { }

void Game::initGame() {
    board.initBoard();

    // Decides who acts first
    currentPlayer = &firstPlayer;
    otherPlayer = &secondPlayer;
    updatePossibleMoves();

    notifyUpdate();
}

void Game::switchCurrentPlayer() {
    if (*currentPlayer == firstPlayer) {
        currentPlayer = &secondPlayer;
        otherPlayer = &firstPlayer;
    } else {
        currentPlayer = &firstPlayer;
        otherPlayer = &secondPlayer;
    }
}

bool Game::checkGameEnd() {
    coordinates coordF, coordS;
    coordF = getFirstPlayerPosition();
    coordS = getSecondPlayerPosition();

    if (coordF.y == 0) {
        winner = &firstPlayer;
        return true;
    } else if (coordS.y == mapSize - 1) {
        winner = &secondPlayer;
        return true;
    } else {
        winner = nullptr;
        return false;
    }
}

void Game::decideTurn() {
    //coordinates position = greatBoard.decideMove();
    //makeTurn(position.x, position.y);
    makeTurn(0,0);
}

void Game::makeTurn(const int x, const int y) {

    // * Build a wall or move
    if (x % 2 != 0 || y % 2 != 0) {
        placeWall(x, y);
    } else {
        movePlayer(x, y);
    }

    switchCurrentPlayer();
    updatePossibleMoves();
    checkGameEnd();
    notifyUpdate();
}

void Game::movePlayer(const int x, const int y) {
    bool isOk = greatBoard.movePlayer(x, y, *currentPlayer, board, possibleMoves);

    // * Returns player a message why his move is wrong
    // ! Using exceptions to do this is actually a terrible idea
    // ! But it's a pain to rewrite whole error system, so I won't do it
    if (!isOk) {
        checker.movePlayerErrorCheck(coordinates {x, y},
                                     getCurrentPlayerPosition(),
                                     getOtherPlayerPosition(),
                                     board);
    }

}

void Game::placeWall(const int x, const int y) {
    if (x % 2 == 0 && y % 2 != 0) {
        checker.placeWallErrorCheck(coordinates {x, y}, horizontal, *currentPlayer, board);
        greatBoard.placeWall(x, y, horizontal, *currentPlayer, board);
    } else if (x % 2 != 0 && y % 2 == 0) {
        checker.placeWallErrorCheck(coordinates {x, y}, vertical, *currentPlayer, board);
        greatBoard.placeWall(x, y, vertical, *currentPlayer, board);
    }
}

void Game::updatePossibleMoves() {
    possibleMoves = greatBoard.calculatePossibleMoves(getCurrentPlayerPosition(),
                                                      getOtherPlayerPosition(),
                                                      board, checker);
}

// * -------------------------------------------------- *
// *                    Getters                         *
// * -------------------------------------------------- *

Board Game::getBoard() {
    return board;
}

std::vector<coordinates> Game::getPossibleMoves() {
    return possibleMoves;
}

bool Game::getCurrentPlayerNeedsInput() {
    return currentPlayer->needsToTakeInput();
}

coordinates Game::getFirstPlayerPosition() {
    return firstPlayer.getPosition();
}

coordinates Game::getSecondPlayerPosition() {
    return secondPlayer.getPosition();
}

coordinates Game::getCurrentPlayerPosition() {
    return currentPlayer->getPosition();
}

coordinates Game::getOtherPlayerPosition() {
    return otherPlayer->getPosition();
}

int Game::getFirstPlayerWalls() {
    return firstPlayer.getWallsCounter();
}

int Game::getSecondPlayerWalls() {
    return secondPlayer.getWallsCounter();
}

const char *Game::getFirstPlayerName() {
    return firstPlayer.getName();
}
const char *Game::getSecondPlayerName() {
    return secondPlayer.getName();
}

const char *Game::getCurrentPlayerName() {
    return currentPlayer->getName();
}

const char *Game::getWinnerName() {
    return winner->getName();
}

// coordinates Game::decideMovePosition() {
//     // Save players initial position
//     coordinates coordF, coordS;
//     coordF = getFirstPlayerPosition();
//     coordS = getSecondPlayerPosition();

//     // Save map
//     Board boardCopy = getBoard();

//     coordinates move = {0, 0};
//     coordinates best = {0, 0};
//     minimax(move, best, 5, true, -1000, 1000);

//     board = boardCopy;
//     // restore players position
//     firstPlayer.move(vector_pair_ii {std::make_pair(coordF.x, coordF.y)});
//     secondPlayer.move(vector_pair_ii {std::make_pair(coordS.x, coordF.y)});

//     return best;
// }

// int Game::shortestPathToRow(IPlayer &player, const int endCol) {
    
//     // Row Queue and Column Queue
//     std::queue<int> rq, cq;

//     // Player position as starting node
//     coordinates coordP = player.getPosition();
//     int sr = coordP.x;
//     int sc = coordP.y;

//     // Variables used to track the number of steps taken.
//     int moveCount = 0;
//     int nodesLeftInLayer = 1;
//     int nodesInNextLayer = 0;

//     // Variable used to track whether the end ever gets reached
//     bool reachedEnd = false;

//     bool visited[mapSize][mapSize];
//     for (int i = 0; i < mapSize; i++) {
//         for (int j = 0; j < mapSize; j++) {
//             visited[i][j] = false;
//         }
//     }

//     // Define the direction vectors for
//     // north, south, east and west.
//     //   ↑      ↓     →        ←
//     int dr[4] = {-2, +2, 0, 0};
//     int dc[4] = {0, 0, +2, -2};

//     // Current position
//     int r = 0;
//     int c = 0;

//     rq.push(sr);
//     cq.push(sc);
//     visited[sr][sc] = true;

//     while (rq.size() > 0) {
//         r = rq.front();
//         c = cq.front();
//         rq.pop();
//         cq.pop();

//         if (c == endCol) {
//             reachedEnd = true;
//             break;
//         }

//         int rr, cc;
//         for (int i = 0; i < 4; i++) {
//             rr = r + dr[i];
//             cc = c + dc[i];

//             // Skip out of bounds locations
//             if (rr < 0 || cc < 0)
//                 continue;
//             if (rr >= mapSize || cc >= mapSize)
//                 continue;

//             // Skip visited locations or walls
//             if (visited[rr][cc])
//                 continue;
            
//             int difX = r - rr;
//             int difY = cc - c;

//             if (difY > 0) {
//                 if (getBoard().getTile(rr, cc-1) == wall) {
//                     continue;
//                 }
//             }
//             else if (difY < 0) {
//                 if (getBoard().getTile(rr, cc+1) == wall) {
//                     continue;
//                 }
//             }
//             else if (difX > 0) {
//                 if (getBoard().getTile(rr+1, cc) == wall) {
//                     continue;
//                 }
//             }
//             else if (difX < 0) {
//                 if (getBoard().getTile(rr-1, cc) == wall) {
//                     continue;
//                 }
//             }
            
//             rq.push(rr);
//             cq.push(cc);

//             visited[rr][cc] = true;
//             ++nodesInNextLayer;
//         }

//         --nodesLeftInLayer;
//         if (nodesLeftInLayer == 0)
//         {
//             nodesLeftInLayer = nodesInNextLayer;
//             nodesInNextLayer = 0;
//             ++moveCount;
//         }
//     }

//     if (reachedEnd) return moveCount;

//     return 0;
// }

// int Game::minimax(coordinates &move, coordinates &best, int depth, bool maximizingPlayer, int alpha, int beta) {
//     if (depth == 0 || checkGameEnd()) {
//         return heuristic(move);
//     }

//     calculatePossibleMoves();
//     // TODO: change possible moves to coordinates vector
//     std::vector<coordinates> moves;
//     for (auto move : possibleMoves) {
//         moves.push_back(coordinates{move.first, move.second}); }
//     std::vector<coordinates> walls = calculateMeaningfulWalls(*currentPlayer);

//     std::vector<coordinates> allPossibleMoves;
//     allPossibleMoves.reserve(moves.size() + walls.size()); // preallocate memory
//     allPossibleMoves.insert(allPossibleMoves.end(), moves.begin(), moves.end());
//     allPossibleMoves.insert(allPossibleMoves.end(), walls.begin(), walls.end());

//     switchCurrentPlayer();

//     coordinates coordCP = getCurrentPlayerPosition();
//     Board returnBoard = getBoard();

//     int score;
//     for (auto move : allPossibleMoves) {
//         makeTurn(move.x, move.y);
//         if (maximizingPlayer) {
//             score = minimax(move, best, --depth, !maximizingPlayer, alpha, beta);
//             // Return values
//             currentPlayer->move(vector_pair_ii{std::make_pair(coordCP.x, coordCP.y)});
//             board = returnBoard;

//             if (score > alpha)
//             {
//                 best = move;
//                 alpha = score;
//             }
//             if (alpha >= beta) { break; }

//             return alpha;
//         } else {
//             score = minimax(move, best, --depth, !maximizingPlayer, alpha, beta);
//             if (score < beta) {
//                 best = move;
//                 beta = score;
//             }
//             if (alpha >= beta) { break; }

//             return beta;
//         }
//     }

//     return 0;
// }

// int Game::heuristic(coordinates &move) {
//     int score = 0;

//     int distance = shortestPathToRow(firstPlayer, 0);
//     int distance2 = shortestPathToRow(secondPlayer, mapSize - 1);
//     distance2 *= -1;

//     int x = move.x;
//     int y = move.y;
//     // * Build a wall
//     if (x % 2 != 0 || y % 2 != 0) {
//         if (x % 2 == 0 && y % 2 != 0) {
//             placeWall(x, y, horizontal);
//         } else if (x % 2 != 0 && y % 2 == 0) {
//             placeWall(x, y, vertical);
//         } else { // * Not allow current move
//             placeWallErrorCheck(x, y, horizontal);
//         }
//     } else {
//         score = distance2 + distance;
//         return -score;
//     }

//     // Recalculate shortest path

//     return -score;
// }

// std::vector<coordinates> Game::calculateMeaningfulWalls(IPlayer &player) {
//     // Possible walls location
//     // x-2 y-1, x y-1, x-2 y+1, x y+1
//     // y-2 x-1, y x-1, y-2 x+1, y x+1

//     coordinates coordP;
//     coordP = player.getPosition();

//     std::vector<coordinates> Walls;

//     int r = 2; // * radius

//     for(int x = coordP.x - r; x <= coordP.x; x+=2) {
//         for (int y = coordP.y - 1; y <= coordP.y + 1; y+=2) {
//             try {
//                 placeWallErrorCheck(x, y, horizontal);
//             } catch(const std::exception& e) {
//                 continue;
//             }

//             Walls.push_back(coordinates{x, y});
//         }
//     }

//     for(int y = coordP.y - r; y <= coordP.y; y+=2) {
//         for (int x = coordP.x - 1; x <= coordP.x + 1; x+=2) {
//             try {
//                 placeWallErrorCheck(x, y, vertical);
//             } catch(const std::exception& e) {
//                 continue;
//             }

//             Walls.push_back(coordinates{x, y});
//         }
//     }

//     return Walls;

// }