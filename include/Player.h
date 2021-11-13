#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>

#include "utility.h"

class IPlayer {
private:
    int m_X;
    int m_Y;
    const char* m_Name;

public:
    virtual ~IPlayer() {};

    virtual const char *getName() const = 0;
    virtual int getWallsCounter() const = 0;
    virtual coordinates getPosition() const = 0;

    virtual void reduceWall() = 0;
    virtual bool needsToTakeInput() = 0;
    virtual void move(const int x, const int y) = 0;

    // rhs means "right hand side"
    bool operator == (const IPlayer &rhs) const {
        return
               this->m_X == rhs.m_X
            && this->m_Y == rhs.m_Y
            && this->m_Name == rhs.m_Name;
    }

private:
    IPlayer& operator=(const IPlayer&);
};

class Player : public IPlayer {
private:
    int m_X;
    int m_Y;

    const char *m_Name;
    
    int m_WallsCounter = WallsAmount;

public:
    Player(const int x, const int y, const char *name);
    Player() = default;
    ~Player() = default;

    const char *getName() const;
    int getWallsCounter() const;
    coordinates getPosition() const;

    void reduceWall();
    bool needsToTakeInput();
    void move(const int x, const int y);
};

#endif // PLAYER_H