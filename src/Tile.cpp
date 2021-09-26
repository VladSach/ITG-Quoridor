#include "Tile.h"

void Tile::setPosition(int x, int y) {
    m_X = x;
    m_Y = y;
}

//@param x,y returning values
int Tile::getPosition(int *x, int *y) {
    // TODO: Add some kind of check for pointers

    *x = m_X;
    *y = m_Y;

    return 0;
}

bool Tile::getWall(unsigned char wall) {
    switch (wall) {
    case leftWall:
        return (m_Walls & leftWall) ? true : false;

    case upperWall:
        return (m_Walls & upperWall) ? true : false;

    case lowerWall:
        return (m_Walls & lowerWall) ? true : false;

    case rightWall:
        return (m_Walls & rightWall) ? true : false;
    
    default:
        return false;
    }
}