#include "Player.h"

Player::Player(int x, int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

const char* Player::getName() {
    return m_Name;
}

//@param x,y returning values
int Player::getPosition(int *x, int *y) {
    // TODO: Add some kind of check for pointers

    *x = m_X;
    *y = m_Y;

    return 0;
}

int Player::getWallsCounter() {
    return m_WallsCounter;
}

void Player::takeWall() {
    --m_WallsCounter;
}

void Player::movePlayer(PlayerDirection direction) {
    // TODO: add check if players are in front of each other
    switch (direction) {
    case left:
        m_X -= 2;
        break;
    
    case up:
        m_Y -= 2;
        break;

    case down:
        m_Y += 2;
        break;
    
    case right:
        m_X += 2;
        break;

    default:
        break;
    }
}


