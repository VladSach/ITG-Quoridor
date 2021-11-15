#include "ErrorHandler.h"

ErrorHandler* ErrorHandler::singleton_ = nullptr;

ErrorHandler *ErrorHandler::GetInstance() {
    if (singleton_ == nullptr) {
        singleton_ = new ErrorHandler();
    }
    return singleton_;
}

void ErrorHandler::movePlayerErrorCheck(const coordinates &move, 
                                      const coordinates &cur, 
                                      const coordinates &other,
                                      const Board &board) {
    const int x = move.x;
    const int y = move.y;

    const int curX = cur.x;
    const int curY = cur.y;
    const int otherX = other.x;
    const int otherY = other.y;

    const int difX = x - curX;
    const int difY = curY - y;

    // Out of bounds
    if (x >= 17 || y >= 17 || x < 0 || y < 0) {
        throw std::invalid_argument(
            "Oof, someone's trying to escape\nNot gonna happen"
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

    if (checkPlayersEncounter(cur, other) &&
        resolvePlayersEncounter(move, cur, other, board)) {
        return;
    }

    unsigned int difXAbs = absQ(difX);
    unsigned int difYAbs = absQ(difY);

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
    if (otherX == x && otherY == y) {
        throw std::invalid_argument(
            "It's already has someone on it"
        );
    } else if (curX == x && curY == y) {
        throw std::invalid_argument(
            "You are aready on it"
        );
    }
}

// * Checks if players in front of each other and solves it
bool ErrorHandler::checkPlayersEncounter(const coordinates &cur,
                                       const coordinates &other){
    int curX = cur.x;
    int curY = cur.y;
    int otherX = other.x;
    int otherY = other.y;

    // P for players
    const int difPX = otherX - curX;
    const int difPY = curY - otherY;
    
    unsigned int difPXAbs = absQ(difPX);
    unsigned int difPYAbs = absQ(difPY);    

    // Are players near each other
    if (difPXAbs > 2 || difPYAbs > 2) { return false; }
            
    return true;
}

bool ErrorHandler::resolvePlayersEncounter(const coordinates &move, 
                                            const coordinates &cur, 
                                            const coordinates &other,
                                            const Board &board) {

    const int x = move.x;
    const int y = move.y;

    const int curX = cur.x;
    const int curY = cur.y;
    const int otherX = other.x;
    const int otherY = other.y;

    kludge.clear();

    // P for players
    const int difPX = otherX - curX;
    const int difPY = curY - otherY;

    const int difX = x - curX;
    const int difY = curY - y;  

    if (difPY > 0) {
        if (difX != 0 || difY != 4 || difPX != 0) { return false; }
        if (board.getTile(curX, curY - 3) == wall) {
            if (board.getTile(curX + 1, curY - 2) != wall) {
                kludge.push_back(coordinates {curX + 2, curY - 2});
            }
            if (board.getTile(curX - 1, curY - 2) != wall) {
                kludge.push_back(coordinates{curX - 2, curY - 2});
            }

            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }

    } else if (difPY < 0) {
        if (difX != 0 || difY != -4 || difPX != 0) { return false; }
        if (board.getTile(curX, curY + 3) == wall) {
            if (board.getTile(curX + 1, curY + 2) != wall) {
                kludge.push_back(coordinates{curX + 2, curY + 2});
            }
            if (board.getTile(curX - 1, curY + 2) != wall) {
                kludge.push_back(coordinates{curX - 2, curY + 2});
            }

            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }

    } else if (difPX > 0) {
        if (difX != 4 || difY != 0 || difPY != 0) { return false; }
        if (board.getTile(curX + 3, curY) == wall) {
            if (board.getTile(curX + 2, curY + 1) != wall) {
                kludge.push_back(coordinates{curX + 2, curY + 2});
            }
            if (board.getTile(curX + 2, curY - 1) != wall) {
                kludge.push_back(coordinates{curX + 2, curY - 2});
            }

            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }

    } else if (difPX < 0) {
        if (difX != -4 || difY != 0 || difPY != 0) { return false; }
        if (board.getTile(curX - 3, curY) == wall) {
            if (board.getTile(curX - 2, curY + 1) != wall) {
                kludge.push_back(coordinates{curX - 2, curY + 2});
            }
            if (board.getTile(curX - 2, curY - 1) != wall) {
                kludge.push_back(coordinates{curX - 2, curY - 2});
            }

            throw std::invalid_argument(
                "Sorry, you can't hop over the wall"
            );
        }
    } 

    return true;
}

void ErrorHandler::placeWallErrorCheck(const coordinates &move, Direction direction,
                                     IPlayer &cur, IPlayer &other, const Board &board) {

    const int x = move.x;
    const int y = move.y;

    // Player has no walls
    if (cur.getWallsCounter() <= 0) {
        throw std::invalid_argument(
            "Sorry, Pal, looks like you're short on walls"
        );
    }

    // TODO: Someone standing there

    // Wall out of bounds
    if (x >= 17 || y >= 17 || x < 0 || y < 0) {
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

    // Closes last path to finish
    if (!isPathExists(cur, board, x, y, direction) ||
        !isPathExists(other, board, x, y, direction)) {
            throw std::invalid_argument(
                "No path - no winner"
            );
    }
}

// BFS on grid
// Checks if there is a path from left upper angle to other side of board
bool ErrorHandler::isPathExists(IPlayer &player, Board boardCopy, 
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
    coordinates pc;
    pc = player.getPosition();
    sr = pc.x;
    sc = pc.y;

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

        if (c == player.getEndY()) {
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

// A kludge to add move in case player can jump over another
// Not cool, but I dont want to rewrite 2 functions cause of this
void ErrorHandler::addMove(std::vector<coordinates> &moves) {
    if (kludge.size() == 0) { return; }

    for (auto e : kludge) {
        moves.push_back(e);
    }
}