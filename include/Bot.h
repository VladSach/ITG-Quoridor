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
    coordinates getPosition() const;

    void move(std::vector<std::pair<int, int>> possibleMovements);
    void placeWall(const int x, const int y, Direction direction, Board& board);
    bool needsToTakeInput();
};

#endif // BOT_H