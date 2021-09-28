#ifndef BOT_H
#define BOT_H

#include "Player.h"

#include <cstdlib>

class Bot : public IPlayer {
private:
    int m_X;
    int m_Y;

    const char *m_Name;
    
    int m_WallsCounter = 10;
  
public:
    Bot(const int x, const int y, const char *name);
    Bot() = default;
    ~Bot() = default;

    const char *getName();
    int getWallsCounter();
    int getPosition(int *x, int *y);

    void takeWall();
    void movePlayer(PlayerDirection direction);
    void doubleMove(PlayerDirection direction);
    void diagonalMove(PlayerDirection direction);
};

#endif // BOT_H