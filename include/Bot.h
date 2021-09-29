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

    const char *getName() const;
    int getWallsCounter() const;
    int getPosition(int *const x, int *const y) const;

    void takeWall();
    void move(std::vector<std::pair<int, int>> possibleMovements);
    bool needsToTakeInput();
};

#endif // BOT_H