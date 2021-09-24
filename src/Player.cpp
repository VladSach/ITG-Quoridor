#include "Player.h"

Player::Player(int x, int y, int wallsAmount) {
    m_X = x;
    m_Y = y;
    m_WallsCounter = wallsAmount;
}

int Player::getPosition(int *x, int *y) {
    // TODO: Add some kind of check for pointers

    *x = m_X;
    *y = m_Y;

    return 0;
}

int Player::getWallsCounter() {
    return m_WallsCounter;
}

void Player::movePlayer(Directions direction) {
    switch (direction) {
    case left:
        --m_X;
        break;
    
    case up:
        --m_Y;
        break;

    case down:
        ++m_Y;
        break;
    
    case right:
        ++m_X;
        break;

    default:
        break;
    }
}


