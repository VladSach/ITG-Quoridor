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
    case left:
        return (m_Walls & left) ? true : false;

    case upper:
        return (m_Walls & upper) ? true : false;

    case lower:
        return (m_Walls & lower) ? true : false;

    case right:
        return (m_Walls & right) ? true : false;
    
    default:
        return false;
    }
}

void Tile::setWall(unsigned char wall) {
    //wall &= lowMask;
    m_Walls |= wall;
}