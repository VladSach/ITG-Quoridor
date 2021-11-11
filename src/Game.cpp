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
    std::pair<int, int> position = decideMovePosition();

    makeTurn(position.first, position.second);
}

void Game::makeTurn(const int x, const int y) {

    // * Build a wall
    if (x % 2 != 0 || y % 2 != 0) {
        if (x % 2 == 0 && y % 2 != 0) {
            placeWall(x, y, horizontal);
        } else if (x % 2 != 0 && y % 2 == 0) {
            placeWall(x, y, vertical);
        } else { // * Not allow current move
            placeWallErrorCheck(x, y, horizontal);
        }
    } else {
        movePlayer(x, y);
    }

    switchCurrentPlayer();
    calculatePossibleMoves();
    checkGameEnd();
    notifyUpdate();
}

void Game::calculatePossibleMoves() {
    coordinates coordCur;
    coordCur = getCurrentPlayerPosition();

    possibleMoves.clear();

    int r = 2; // * radius

    if(checkPlayersEncounter()) r = 4;

    for(int x = coordCur.x - r; x <= coordCur.x + r; x+=2) {
        for (int y = coordCur.y - r; y <= coordCur.y + r; y+=2) {
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
    bool found = false;

    if (currentPlayer->needsToTakeInput()) {
        for (auto e : possibleMoves) {
            if (e.first == x && e.second == y) {
                found = true;
            }
        }

        if (found) {
            pM.push_back(std::make_pair(x, y));
        } else {
            movePlayerErrorCheck(x, y);
        }
    } else { pM = possibleMoves; }

    currentPlayer->move(pM);
}

void Game::placeWall(const int x, const int y, Direction direction) {
    placeWallErrorCheck(x, y, direction);

    currentPlayer->placeWall(x, y, direction, board);
}

void Game::movePlayerErrorCheck(const int x, const int y) {
    // Out of bounds
    if (x > 17 || y > 17 || x < 0 || y < 0) {
        throw std::invalid_argument(
            "Oof, someone's trying to escape\nNot gonna happen"
        );
    }

    coordinates coordF, coordS;
    coordF = getFirstPlayerPosition();
    coordS = getSecondPlayerPosition();


    coordinates coordCur;
    coordCur = getCurrentPlayerPosition();
    int curX = coordCur.x;
    int curY = coordCur.y;
    

    const int difX = x - curX;
    const int difY = curY - y;

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

    if (checkPlayersEncounter() && 
        resolvePlayersEncounter(x, y)) {
            return;
    }

    // * No need for cmath library and abs()
    // * http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
    const int maskX = difX >> (sizeof(int) * __CHAR_BIT__ - 1);
    const int maskY = difY >> (sizeof(int) * __CHAR_BIT__ - 1);
    unsigned int difXAbs = (difX + maskX) ^ maskX;
    unsigned int difYAbs = (difY + maskY) ^ maskY;

    // Wrong movement
    if (difXAbs == 2 && difYAbs == 2) {
        throw std::invalid_argument(
            "You're not allowed to move diagonally ... most of the time"
        );
    }

    // More than 1 tile jump
    if (difXAbs > 2 || difYAbs > 2) {
        throw std::invalid_argument(
            "OnE tIlE aT a TiMe"
        );
    }

    // Tile is occupied
    if ((coordF.x == x && coordF.y == y) ||
        (coordS.x == x && coordS.y == y)) {
            throw std::invalid_argument(
                "It's already has someone on it"
            );
    }
}
// * Checks if players in front of each other and solves it
bool Game::checkPlayersEncounter(){
    coordinates coordCur = getCurrentPlayerPosition();
    coordinates coordOther = getOtherPlayerPosition();
    int curX = coordCur.x;
    int curY = coordCur.y;
    int otherX = coordOther.x;
    int otherY = coordOther.y;

    // P for players
    const int difPX = otherX - curX;
    const int difPY = curY - otherY;
    
    // * No need for cmath library and abs()
    // * http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
    const int maskX = difPX >> (sizeof(int) * __CHAR_BIT__ - 1);
    const int maskY = difPY >> (sizeof(int) * __CHAR_BIT__ - 1);
    unsigned int difPXAbs = (difPX + maskX) ^ maskX;
    unsigned int difPYAbs = (difPY + maskY) ^ maskY;    

    // Are players near each other
    if (difPXAbs > 2 || difPYAbs > 2) { return false; }
            
    return true;
}

bool Game::resolvePlayersEncounter(const int x, const int y) {
    coordinates coordCur = getCurrentPlayerPosition();
    coordinates coordOther = getOtherPlayerPosition();
    int curX = coordCur.x;
    int curY = coordCur.y;
    int otherX = coordOther.x;
    int otherY = coordOther.y;

    // P for players
    const int difPX = otherX - curX;
    const int difPY = curY - otherY;

    const int difX = x - curX;
    const int difY = curY - y;  

    if (difPY > 0) {
        if (difX != 0 || difY != 4 || difPX != 0) { return false; }
        if (board.getTile(curX, curY - 3) == wall) {
            if (board.getTile(curX + 1, curY - 2) != wall) {
                possibleMoves.push_back(std::make_pair(curX+2, curY-2));
            }
            if (board.getTile(curX - 1, curY - 2) != wall) {
                possibleMoves.push_back(std::make_pair(curX-2, curY-2));
            }

            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }

    } else if (difPY < 0) {
        if (difX != 0 || difY != -4 || difPX != 0) { return false; }
        if (board.getTile(curX, curY + 3) == wall) {
            if (board.getTile(curX + 1, curY + 2) != wall) {
                possibleMoves.push_back(std::make_pair(curX+2, curY+2));
            }
            if (board.getTile(curX - 1, curY + 2) != wall) {
                possibleMoves.push_back(std::make_pair(curX-2, curY+2));
            }

            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }

    } else if (difPX > 0) {
        if (difX != 4 || difY != 0 || difPY != 0) { return false; }
        if (board.getTile(curX + 3, curY) == wall) {
            if (board.getTile(curX + 2, curY + 1) != wall) {
                possibleMoves.push_back(std::make_pair(curX+2, curY+2));
            }
            if (board.getTile(curX + 2, curY - 1) != wall) {
                possibleMoves.push_back(std::make_pair(curX+2, curY-2));
            }

            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }

    } else if (difPX < 0) {
        if (difX != -4 || difY != 0 || difPY != 0) { return false; }
        if (board.getTile(curX - 3, curY) == wall) {
            if (board.getTile(curX - 2, curY + 1) != wall) {
                possibleMoves.push_back(std::make_pair(curX-2, curY+2));
            }
            if (board.getTile(curX - 2, curY - 1) != wall) {
                possibleMoves.push_back(std::make_pair(curX-2, curY-2));
            }

            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    } 

    return true;
}

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
            "Look like a half measure to me"
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
int Game::isPathExists(IPlayer &player, const int endCol, Board boardCopy, 
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
    coordinates coordP = player.getPosition();
    int sr = coordP.x;
    int sc = coordP.y;

    // Variables used to track the number of steps taken.
    int moveCount = 0;
    int nodesLeftInLayer = 1;
    int nodesInNextLayer = 0;

    // Variable used to track whether the end ever gets reached
    bool reachedEnd = false;

    bool visited[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
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

    while (rq.size() > 0) {
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

    if (reachedEnd) return moveCount;

    return 0;
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
    return (*currentPlayer == firstPlayer) ?
    secondPlayer.getPosition() :
    firstPlayer.getPosition();
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

pair_ii Game::decideMovePosition() {
    // Save players initial position
    coordinates coordF, coordS;
    coordF = getFirstPlayerPosition();
    coordS = getSecondPlayerPosition();

    // Save map
    Board boardCopy = getBoard();

    coordinates move = {0, 0};
    minimax(move, 5, true, -1000, 1000);

    board = boardCopy;
    // restore players position and move player
    
}

int Game::shortestPathToRow(IPlayer &player, const int endCol, Board boardCopy) {
    
    // Row Queue and Column Queue
    std::queue<int> rq, cq;

    // Player position as starting node
    coordinates coordP = player.getPosition();
    int sr = coordP.x;
    int sc = coordP.y;

    // Variables used to track the number of steps taken.
    int moveCount = 0;
    int nodesLeftInLayer = 1;
    int nodesInNextLayer = 0;

    // Variable used to track whether the end ever gets reached
    bool reachedEnd = false;

    bool visited[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
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

    while (rq.size() > 0) {
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

    if (reachedEnd) return moveCount;

    return 0;
}

int Game::minimax(coordinates& action, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0 || checkGameEnd()) {
        return heuristic();
    }

    calculatePossibleMoves();
    // TODO: change possible moves to coordinates vector
    std::vector<coordinates> moves;
    for (auto move : possibleMoves) {
        moves.push_back(coordinates{move.first, move.second}); }
    std::vector<coordinates> walls = calculateMeaningfulWalls(*currentPlayer);

    std::vector<coordinates> allPossibleMoves;
    allPossibleMoves.reserve(moves.size() + walls.size()); // preallocate memory
    allPossibleMoves.insert(allPossibleMoves.end(), moves.begin(), moves.end());
    allPossibleMoves.insert(allPossibleMoves.end(), walls.begin(), walls.end());


    int score;
    for (auto move : allPossibleMoves) {
        if (maximizingPlayer) {
            score = minimax(action, --depth, !maximizingPlayer, alpha, beta);
            if (score > alpha) {
                if (depth == 0) { action = move; } // ? Условие
                alpha = score;
            }
            if (alpha >= beta) { break; }

            return alpha;
        } else {
            score = minimax(action, --depth, !maximizingPlayer, alpha, beta);
            if (score < beta) {
                if (depth == 0) { action = move; } // ? Условие
                beta = score;
            }
            if (alpha >= beta) { break; }

            return beta;
        }
    }

    // ? Change player here?
}

int Game::heuristic() {
    int score = 0;

    Board boardCopy = getBoard();
    int distance = shortestPathToRow(firstPlayer, 0, boardCopy);
    int distance2 = shortestPathToRow(secondPlayer, mapSize - 1, boardCopy);
    distance2 *= -1;

    score = distance2 + distance;

    return -score;
}

std::vector<coordinates> Game::calculateMeaningfulWalls(IPlayer &player) {
    // Possible walls location
    // x-2 y-1, x y-1, x-2 y+1, x y+1
    // y-2 x-1, y x-1, y-2 x+1, y x+1

    coordinates coordP;
    coordP = player.getPosition();

    std::vector<coordinates> Walls;

    int r = 2; // * radius

    for(int x = coordP.x - r; x <= coordP.x; x+=2) {
        for (int y = coordP.y - 1; y <= coordP.y + 1; y+=2) {
            try {
                placeWallErrorCheck(x, y, horizontal);
            } catch(const std::exception& e) {
                continue;
            }

            Walls.push_back(coordinates{x, y});
        }
    }

    for(int y = coordP.y - r; y <= coordP.y; y+=2) {
        for (int x = coordP.x - 1; x <= coordP.x + 1; x+=2) {
            try {
                placeWallErrorCheck(x, y, vertical);
            } catch(const std::exception& e) {
                continue;
            }

            Walls.push_back(coordinates{x, y});
        }
    }

    return Walls;

}