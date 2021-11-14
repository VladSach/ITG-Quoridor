#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot : public IPlayer {
private:
    int m_X;
    int m_Y;
    int m_EndY;

    const char *m_Name;
    
    int m_WallsCounter = WallsAmount;
  
public:
    Bot(const int x, const int y, const char *name);
    Bot() = default;
    ~Bot() = default;

    const char *getName() const;
    int getWallsCounter() const;
    coordinates getPosition() const;
    int getEndY() const;

    void reduceWall();
    void returnWall();
    bool needsToTakeInput();
    void move(const int x, const int y);

    Bot& operator=(const Bot& rhs) {
        // Guard self assignment
        if (this == &rhs)
            return *this;

        this->m_X = rhs.m_X;
        this->m_Y = rhs.m_Y;
        this->m_Name = rhs.m_Name;
        this->m_EndY = rhs.m_EndY;

        return *this;
    };
};

#endif // BOT_H