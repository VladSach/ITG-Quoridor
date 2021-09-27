#include "Player.h"

Player::Player(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

const char* Player::getName() {
    return m_Name;
}

// @param x,y returning values
int Player::getPosition(int *x, int *y) {
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


void Player::doubleMove(PlayerDirection direction) {
    switch (direction) {
    case left:
        m_X -= 4;
        break;

    case up:
        m_Y -= 4;
        break;

    case down:
        m_Y += 4;
        break;
    
    case right:
        m_X += 4;
    
    default:
        break;
    }
}

void Player::diagonalMove(PlayerDirection direction) {
    switch (direction) {
    case upper_left:
        m_X -= 2;
        m_Y -= 2;
        break;
    
    case upper_right:
        m_X += 2;
        m_Y -= 2;
        break;

    case lower_left:
        m_X -= 2;
        m_Y += 2;
        break;
    
    case lower_right:
        m_X += 2;
        m_Y += 2;
        break;

    default:
        break;
    }
}