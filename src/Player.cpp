#include "Player.h"

Player::Player(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

const char* Player::getName() const {
    return m_Name;
}

coordinates Player::getPosition() const {
    return coordinates{m_X, m_Y};
}

int Player::getWallsCounter() const {
    return m_WallsCounter;
}

void Player::move(std::vector<coordinates> possibleMovements) { 
    m_X = possibleMovements[0].x;
    m_Y = possibleMovements[0].y;
}

void Player::placeWall(const int x, const int y, Direction direction, Board& board) {
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

bool Player::needsToTakeInput() {
    return true;
}
