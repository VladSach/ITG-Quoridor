#include "Player.h"

Player::Player(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

void Player::move(const int x, const int y) { 
    m_X = x;
    m_Y = y;
}

void Player::reduceWall() {
    --m_WallsCounter;
}

bool Player::needsToTakeInput() {
    return true;
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