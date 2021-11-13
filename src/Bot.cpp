#include "Bot.h"

Bot::Bot(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

const char* Bot::getName() const {
    return m_Name;
}

coordinates Bot::getPosition() const {
    return coordinates{m_X, m_Y};
}

int Bot::getWallsCounter() const {
    return m_WallsCounter;
}

void Bot::move(std::vector<coordinates> possibleMovements) {
    int randomMove = rand() % possibleMovements.size();

    m_X = possibleMovements[randomMove].x;
    m_Y = possibleMovements[randomMove].y;
}

void Bot::placeWall(const int x, const int y, Direction direction, Board& board) {    
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
    --m_WallsCounter;
}

bool Bot::needsToTakeInput() {
    return false;
}