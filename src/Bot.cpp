#include "Bot.h"

Bot::Bot(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

const char* Bot::getName() {
    return m_Name;
}

// @param x,y returning values
int Bot::getPosition(int *x, int *y) {
    *x = m_X;
    *y = m_Y;

    return 0;
}

int Bot::getWallsCounter() {
    return m_WallsCounter;
}

void Bot::takeWall() {
    --m_WallsCounter;
}

void Bot::movePlayer(PlayerDirection direction =
                    static_cast<PlayerDirection>(rand() % last)) {
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


void Bot::doubleMove(PlayerDirection direction) {
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

void Bot::diagonalMove(PlayerDirection direction) {
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
