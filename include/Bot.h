#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot : public IPlayer {
private:
    int m_X;
    int m_Y;

    const char *m_Name;
    
    int m_WallsCounter = WallsAmount;
  
public:
    Bot(const int x, const int y, const char *name);
    Bot() = default;
    ~Bot() = default;

    const char *getName() const;
    int getWallsCounter() const;
    coordinates getPosition() const;

    void reduceWall();
    bool needsToTakeInput();
    void move(const int x, const int y);
};

#endif // BOT_H