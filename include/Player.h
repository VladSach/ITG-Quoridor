#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>

#include "utility.h"

class IPlayer {
private:
    int m_X;
    int m_Y;
    int m_EndY;
    const char* m_Name;

public:
    virtual ~IPlayer() {};

    virtual const char *getName() const = 0;
    virtual int getWallsCounter() const = 0;
    virtual coordinates getPosition() const = 0;
    virtual int getEndY() const = 0;

    virtual void reduceWall() = 0;
    virtual void returnWall() = 0;
    virtual bool needsToTakeInput() = 0;
    virtual void move(const int x, const int y) = 0;

    // rhs means "right hand side"
    bool operator == (const IPlayer &rhs) const {
        return this->m_X == rhs.m_X
            && this->m_Y == rhs.m_Y
            && this->m_Name == rhs.m_Name
            && this->m_EndY == rhs.m_EndY;
    }

private:
    IPlayer& operator=(const IPlayer&);
};

class Player : public IPlayer {
private:
    int m_X;
    int m_Y;
    int m_EndY;

    const char *m_Name;
    
    int m_WallsCounter = WallsAmount;

public:
    Player(const int x, const int y, const char *name);
    Player() = default;
    ~Player() = default;

    const char *getName() const;
    int getWallsCounter() const;
    coordinates getPosition() const;
    int getEndY() const;

    void reduceWall();
    void returnWall();
    bool needsToTakeInput();
    void move(const int x, const int y);

    Player& operator=(const Player& rhs) {
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

#endif // PLAYER_H