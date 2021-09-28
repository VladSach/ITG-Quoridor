#include "Game.h"

Game::Game(IPlayer &fp, IPlayer &sp) : 
           firstPlayer(fp), secondPlayer(sp) {
}

void Game::initGame() {
    board.initBoard();

    // Decides who acts first
    currentPlayer = &firstPlayer;
    calculatePossibleMoves();

    notifyUpdate();
}

void Game::switchCurrentPlayer() {
    (*currentPlayer == firstPlayer) ?
    currentPlayer = &secondPlayer :
    currentPlayer = &firstPlayer;
}

bool Game::checkGameEnd() {
    int x1, y1, x2, y2;
    firstPlayer.getPosition(&x1, &y1);
    secondPlayer.getPosition(&x2, &y2);

    if (y1 == 0) {
        winner = &firstPlayer;
        return true;
    } else if (y2 == mapSize - 1) {
        winner = &secondPlayer;
        return false;
    } else {
        winner = nullptr;
        return false;
    }
}

void Game::makeTurn(const int x, const int y) {

    // * Build a wall
    if (x % 2 != 0 || y % 2 != 0) {
        if (x % 2 == 0 && y % 2 != 0) {
            placeWall(x, y, horizontal);
        } else if (x % 2 != 0 && y % 2 == 0) {
            placeWall(x, y, vertical);
        } else {} // * Skip move

    } else { // * Move player
        movePlayer(x, y);
    }

    switchCurrentPlayer();
    calculatePossibleMoves();
    checkGameEnd();
    notifyUpdate();
}

void Game::calculatePossibleMoves() {
    int curX, curY;
    currentPlayer->getPosition(&curX, &curY);

    possibleMoves.clear();

    for(int x = curX - 2; x <= curX + 2; x+=2) {
        for (int y = curY - 2; y <= curY + 2; y+=2) {
            try {
                movePlayerErrorCheck(x, y);
            } catch(const std::exception& e) {
                continue;
            }

            possibleMoves.push_back(std::make_pair(x, y));
        }
    }

}

void Game::movePlayer(const int x, const int y) {
    std::vector<std::pair<int, int>> pM;

    if (currentPlayer->needsToTakeInput()) {
        movePlayerErrorCheck(x, y);
        for (auto e : possibleMoves) {
            if (e.first == x && e.second == y) {
                pM.push_back(std::make_pair(x, y));
            }
        }
    } else pM = possibleMoves;

    currentPlayer->move(pM);

}

void Game::placeWall(const int x, const int y, Direction direction) {
    placeWallErrorCheck(x, y, direction);

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

    currentPlayer->takeWall();
}

void Game::movePlayerErrorCheck(const int x, const int y) {
    // Out of bounds
    if (x > 17 || y > 17 || x < 0 || y < 0) {
        throw std::invalid_argument(
            "Oof, someone's trying to escape\nNot gonna happen"
        );
    }

    // Tile is occupied
    int x1, x2, y1, y2;
    firstPlayer.getPosition(&x1, &y1);
    secondPlayer.getPosition(&x2, &y2);

    if ((x1 == x && y1 == y) ||
        (x2 == x && y2 == y)) {
            throw std::invalid_argument(
                "It's already has someone on it"
            );
        }

    // Wrong movement
    //if (checkPlayersEncounter(x, y)) continue;
    int curX, curY;
    currentPlayer->getPosition(&curX, &curY);

    const int difX = x - curX;
    const int difY = curY - y;

    // * No need for cmath library and abs()
    // * http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
    const int maskX = difX >> (sizeof(int) * __CHAR_BIT__ - 1);
    const int maskY = difY >> (sizeof(int) * __CHAR_BIT__ - 1);
    unsigned int difXAbs = (difX + maskX) ^ maskX;
    unsigned int difYAbs = (difY + maskY) ^ maskY;

    if (difXAbs == 2 && difYAbs == 2) {
        throw std::invalid_argument(
            "You're not allowed to move diagonally ... most of the time"
        );
    }

    if (difXAbs > 2 || difYAbs > 2) {
        throw std::invalid_argument(
            "OnE tIlE aT a TiMe"
        );
    }

    // Wall on the path
    if (difY > 0) {
        if (board.getTile(curX, curY-1) == wall) {
            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    }
    else if (difY < 0) {
        if (board.getTile(curX, curY+1) == wall) {
            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    }
    else if (difX > 0) {
        if (board.getTile(curX+1, curY) == wall) {
            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    }
    else if (difX < 0) {
        if (board.getTile(curX-1, curY) == wall) {
            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    }
}

// // * Checks if players in front of each other and solves it
// bool Game::checkPlayersEncounter(const int x, const int y){
//     // ! God, this is awful
//     int curX, curY, otherX, otherY;
//     currentPlayer->getPosition(&curX, &curY);
//     switchCurrentPlayer();
//     currentPlayer->getPosition(&otherX, &otherY);
//     switchCurrentPlayer();

//     // P for players
//     const int difPX = curX - otherX;
//     const int difPY = curY - otherY;
    
//     // Are players near each other
//     if (difPX > 2 || difPY > 2) return false;

//     const int difX = x - curX;
//     const int difY = curY - y; 
    
//     // * No need for cmath library and abs()
//     // * http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
//     const int maskX = difX >> (sizeof(int) * __CHAR_BIT__ - 1);
//     const int maskY = difY >> (sizeof(int) * __CHAR_BIT__ - 1);
//     unsigned int difXAbs = (difX + maskX) ^ maskX;
//     unsigned int difYAbs = (difY + maskY) ^ maskY;

//     // ! Fix bug when player goes back from other
//     // Are player wants to overstep another
//     if (!((difX == 0 && difYAbs == 4) || 
//         (difY == 0 && difXAbs == 4))) {
//             return false;
//         }

//     // TODO: if there is a wall

//     if      (difY > 0) currentPlayer->doubleMove(up);
//     else if (difY < 0) currentPlayer->doubleMove(down);
//     else if (difX > 0) currentPlayer->doubleMove(right);
//     else if (difX < 0) currentPlayer->doubleMove(left);

//     switchCurrentPlayer();
//     checkGameEnd();
//     notifyUpdate();
            
//     return true;
// }

void Game::placeWallErrorCheck(const int x, const int y, Direction direction) {
    // Wall out of bounds
    if (x > 17 || y > 17 || x < 0 || y < 0) {
        throw std::invalid_argument(
            "What's the point if you can't use it?"
        );
    }

    // Wall half out of bounds
    if ((x > 14 && direction == horizontal ) ||
        (y > 14 && direction == vertical)) {
        throw std::invalid_argument(
            "Look like a half measure to me (;¬_¬)"
        );
    }

    // Block only one tile
    if (x % 2 != 0 && y % 2 != 0) {
        throw std::invalid_argument(
            "You should always block two tiles"
        );
    }

    // Place wall on wall or wall on tile
    switch (direction) {
    case horizontal:
        if(board.getTile(x, y) == wall || 
           board.getTile(x+1, y) == wall ||
           board.getTile(x+2, y) == wall) { 
                throw std::invalid_argument(
                    "Hey, there's already a wall"
                );
        }

        if (board.getTile(x, y) == tile ||
            board.getTile(x+1, y) == tile ||
            board.getTile(x+2, y) == tile) {
                throw std::invalid_argument(
                    "You can't build a wall here, we walk on this"
                );
            }

        break;

    case vertical:
        if(board.getTile(x, y) == wall || 
           board.getTile(x, y+1) == wall ||
           board.getTile(x, y+2) == wall) {
                throw std::invalid_argument(
                    "Hey, there's already a wall"
                );
        }

        if (board.getTile(x, y) == tile ||
            board.getTile(x, y+1) == tile ||
            board.getTile(x, y+2) == tile) {
                throw std::invalid_argument(
                    "You can't build a wall here, we walk on this"
                );
            }

        break;

    default:
        break;
    }

    // Player has no walls
    if (currentPlayer->getWallsCounter() == 0) {
        throw std::invalid_argument(
            "Sorry, Pal, looks like you're short on walls"
        );
    }

    // Closes last path to finish
    Board boardCopy = getBoard();
    if (!isPathExists(firstPlayer, 0, boardCopy, x, y, direction) ||
        !isPathExists(secondPlayer, mapSize-1, boardCopy, x, y, direction)) {
            throw std::invalid_argument(
                "What about healthy competition?"
            );
    }
}

// BFS on grid
bool Game::isPathExists(IPlayer &player, const int endCol, Board boardCopy, 
                        const int x, const int y, Direction direction) {

    switch (direction) {
    case horizontal:
        boardCopy.placeWall(x, y);
        boardCopy.placeWall(x+1, y);
        boardCopy.placeWall(x+2, y);
        break;
    
    case vertical:
        boardCopy.placeWall(x, y);
        boardCopy.placeWall(x, y+1);
        boardCopy.placeWall(x, y+2); 
        break;

    default:
        break;
    }
    
    // Row Queue and Column Queue
    std::queue<int> rq, cq;

    // Player position as starting node
    int sr, sc;
    player.getPosition(&sr, &sc);

    // Variables used to track the number of steps taken.
    int moveCount = 0;
    int nodesLeftInLayer = 1;
    int nodesInNextLayer = 0;

    // Variable used to track whether the end ever gets reached
    bool reachedEnd = false;

    bool visited[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            visited[i][j] = false;
        }
    }

    // Define the direction vectors for
    // north, south, east and west.
    //   ↑      ↓     →        ←
    int dr[4] = {-2, +2, 0, 0};
    int dc[4] = {0, 0, +2, -2};

    // Current position
    int r = 0;
    int c = 0;

    rq.push(sr);
    cq.push(sc);
    visited[sr][sc] = true;

    while (rq.size() > 0)
    {
        r = rq.front();
        c = cq.front();
        rq.pop();
        cq.pop();

        if (c == endCol) {
            reachedEnd = true;
            break;
        }

        int rr, cc;
        for (int i = 0; i < 4; i++) {
            rr = r + dr[i];
            cc = c + dc[i];

            // Skip out of bounds locations
            if (rr < 0 || cc < 0)
                continue;
            if (rr >= mapSize || cc >= mapSize)
                continue;

            // Skip visited locations or walls
            if (visited[rr][cc])
                continue;
            
            int difX = r - rr;
            int difY = cc - c;

            if (difY > 0) {
                if (boardCopy.getTile(rr, cc-1) == wall) {
                    continue;
                }
            }
            else if (difY < 0) {
                if (boardCopy.getTile(rr, cc+1) == wall) {
                    continue;
                }
            }
            else if (difX > 0) {
                if (boardCopy.getTile(rr+1, cc) == wall) {
                    continue;
                }
            }
            else if (difX < 0) {
                if (boardCopy.getTile(rr-1, cc) == wall) {
                    continue;
                }
            }
            
            rq.push(rr);
            cq.push(cc);

            visited[rr][cc] = true;
            ++nodesInNextLayer;
        }

        --nodesLeftInLayer;
        if (nodesLeftInLayer == 0)
        {
            nodesLeftInLayer = nodesInNextLayer;
            nodesInNextLayer = 0;
            ++moveCount;
        }
    }

    if (reachedEnd) return true;

    return false;
}

Board Game::getBoard() {
    return board;
}

std::vector<std::pair<int, int>> Game::getPossibleMoves() {
    return possibleMoves;
}

bool Game::getCurrentPlayerNeedsInput() {
    return currentPlayer->needsToTakeInput();
}

void Game::getFirstPlayerPosition(int *x, int *y) {
    firstPlayer.getPosition(x, y);
}

void Game::getSecondPlayerPosition(int *x, int *y) {
    secondPlayer.getPosition(x, y);
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
