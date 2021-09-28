#include "Player.h"

Player::Player(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

const char* Player::getName() const {
    return m_Name;
}

// @param x,y returning values
int Player::getPosition(int *const x, int *const y) const {
    *x = m_X;
    *y = m_Y;

    return 0;
}

int Player::getWallsCounter() const {
    return m_WallsCounter;
}

void Player::takeWall() {
    --m_WallsCounter;
}

void Player::move(std::vector<std::pair<int, int>> possibleMovements) { 
    m_X = possibleMovements[0].first;
    m_Y = possibleMovements[0].second;
}

bool Player::needsToTakeInput() {
    return true;
}
