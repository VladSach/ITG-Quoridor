#include "MoveChooser.h"

coordinates MoveChooser::decideMove(Board board, GreatBoard &gb, Bot bot, Player player) {
    this->gb = gb;
    this->bot = bot;
    this->board = board;
    this->player = player;

    coordinates move = {0, 0};
    coordinates best = {0, 0};

    // * Safety major
    std::vector<coordinates> moves;
    coordinates botCoord = bot.getPosition();
    coordinates playerCoord = player.getPosition();
    moves = gb.calculatePossibleMoves(botCoord, playerCoord, board);

    // If bot has no walls just find shortest path
    if (bot.getWallsCounter() == 0) {
        int scoreB = 100;
        unsigned int indexB = 0;
        int score = 0;
        for (size_t i = 0; i < moves.size(); i++) {
            bot.move(moves[i].x, moves[i].y);
            score = shortestPathToRow(bot, bot.getEndY());
            if (score <= scoreB) {
                scoreB = score;
                indexB = i;
            }
        }
        best.x = moves[indexB].x;
        best.y = moves[indexB].y;
    } else {
        minimax(move, best, 10, true, -1000, 1000);
    }

    bool found = false;

    for (auto e : moves) {
        if (e.x == best.x && e.y == best.y) {
            found = true;
        }
    }
    if (best.x % 2 != 0 || best.y % 2 != 0) {
        found = true;
    }

    if(!found) {
        move = {0, 0};
        best = {0, 0};
        minimax(move, best, 1, true, -1000, 1000);
    }

    return best;

}

int MoveChooser::minimax(coordinates &move, coordinates &best, int depth, 
                         bool maximizingPlayer, int alpha, int beta) {

    if (depth <= 0 || checkWinCondition()) {
        return heuristic(move, !maximizingPlayer);
    }

    coordinates botCoord = bot.getPosition();
    coordinates playerCoord = player.getPosition();

    // ? Why calculate walls if they may not be used ?
    // ? Why go left or right if there is no wall ahead ?
    std::vector<coordinates> moves, walls, allPossibleMoves;
    if (maximizingPlayer) {
        moves = gb.calculatePossibleMoves(botCoord, playerCoord, board);
        walls = gb.calculateMeaningfulWalls(player, bot, board, 2);
    } else {
        moves = gb.calculatePossibleMoves(playerCoord, botCoord, board);
        walls = gb.calculateMeaningfulWalls(bot, player, board, 2);
    }

    allPossibleMoves.reserve(moves.size() + walls.size()); // preallocate memory
    allPossibleMoves.insert(allPossibleMoves.end(), moves.begin(), moves.end());
    allPossibleMoves.insert(allPossibleMoves.end(), walls.begin(), walls.end());

    int score = 0;
    
    if (maximizingPlayer) {
        for (auto move : allPossibleMoves) {
            makeTurn(move.x, move.y, bot, moves);
            //drawMap(board, maximizingPlayer, move);
            score = minimax(move, best, --depth, !maximizingPlayer, alpha, beta);

            // Return values
            bot.move(botCoord.x, botCoord.y);
            if (move.x % 2 != 0 || move.y % 2 != 0) { 
                freeWall(move.x, move.y, bot);
            }

            if (score > alpha) {
                best.x = move.x;
                best.y = move.y;
                alpha = score;
            }
            if (alpha >= beta) { break; }
        }

        return alpha;
    } else {
        for (auto move : allPossibleMoves) {
            makeTurn(move.x, move.y, player, moves);

            score = minimax(move, best, --depth, !maximizingPlayer, alpha, beta);

            // Return values
            player.move(playerCoord.x, playerCoord.y);
            if (move.x % 2 != 0 || move.y % 2 != 0) { 
                freeWall(move.x, move.y, player);
            }

            if (score < beta) {
                beta = score;
            }
            if (alpha >= beta) { break; }
        }

        return beta;
    }
}

int MoveChooser::heuristic(coordinates &move, bool maximizingPlayer) {
    int score = 0;
    int x = move.x;
    int y = move.y;

    // Delete wall so path can be found before and after it placement
    if (x % 2 == 0 && y % 2 == 0) {
        if (maximizingPlayer) { freeWall(x, y, bot); }
        else                  { freeWall(x, y, player); }
    }

    int distance = shortestPathToRow(bot, bot.getEndY());
    int distance2 = shortestPathToRow(player, player.getEndY());

    // If that's a changing position move
    // Or opponent have path longer than current player
    // Then there is no need to place a wall
    if ((x % 2 == 0 && y % 2 == 0) 
        || (maximizingPlayer && (distance < distance2)) 
        || (!maximizingPlayer && (distance > distance2))) {
            score = distance2 - distance;
            return score;
    } else {
        if (maximizingPlayer) { placeWall(x, y, bot); }
        else                  { placeWall(x, y, player); }
    }

    // Recalculate shortest path for opponent
    int distanceAfterWall = (maximizingPlayer)      ? 
        shortestPathToRow(player, player.getEndY()) :
        shortestPathToRow(bot, bot.getEndY());

    // Was this wall helpful?
    if (maximizingPlayer) {
        score = (distanceAfterWall > distance2) ? 100 : -1000;
    } else {
        score = (distanceAfterWall > distance) ? 100 : -1000;
    }

    return score;
}

bool MoveChooser::checkWinCondition() {
    coordinates coordBot, coordPlayer;
    coordBot = bot.getPosition();
    coordPlayer = player.getPosition();

    if      (coordBot.y == bot.getEndY()) { return true; }
    else if (coordPlayer.y == player.getEndY()) { return true; }

    return false;
}

int MoveChooser::shortestPathToRow(IPlayer &player, const int endCol) {
    
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
                if (board.getTile(rr, cc-1) == wall) {
                    continue;
                }
            }
            else if (difY < 0) {
                if (board.getTile(rr, cc+1) == wall) {
                    continue;
                }
            }
            else if (difX > 0) {
                if (board.getTile(rr+1, cc) == wall) {
                    continue;
                }
            }
            else if (difX < 0) {
                if (board.getTile(rr-1, cc) == wall) {
                    continue;
                }
            }
            
            rq.push(rr);
            cq.push(cc);

            visited[rr][cc] = true;
            ++nodesInNextLayer;
        }

        --nodesLeftInLayer;
        if (nodesLeftInLayer == 0) {
            nodesLeftInLayer = nodesInNextLayer;
            nodesInNextLayer = 0;
            ++moveCount;
        }
    }

    if (reachedEnd) return moveCount;

    return 0;
}

void MoveChooser::makeTurn(const int x, const int y, IPlayer &player, std::vector<coordinates> moves) {
    // * Build a wall or move
    if (x % 2 != 0 || y % 2 != 0) {
        placeWall(x, y, player);
    } else {
        gb.movePlayer(x, y, player, board, moves);
    }
}

void MoveChooser::placeWall(const int x, const int y, IPlayer &player) {
    if (x % 2 == 0 && y % 2 != 0) {
        gb.placeWall(x, y, horizontal, player, board);
    } else if (x % 2 != 0 && y % 2 == 0) {
        gb.placeWall(x, y, vertical, player, board);
    }
}

void MoveChooser::freeWall(const int x, const int y, IPlayer &player) {
    if (x % 2 == 0 && y % 2 != 0) {
        gb.freeWall(x, y, horizontal, player, board);
    } else if (x % 2 != 0 && y % 2 == 0) {
        gb.freeWall(x, y, vertical, player, board);
    }
}