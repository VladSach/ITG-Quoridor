#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>

#include "Board.h"
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

    virtual void move(std::vector<std::pair<int, int>> possibleMovements) = 0;
    virtual void placeWall(const int x, const int y, Direction direction, Board& board) = 0;
    virtual bool needsToTakeInput() = 0;

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
    
    int m_WallsCounter = 10;

public:
    Player(const int x, const int y, const char *name);
    Player() = default;
    ~Player() = default;

    const char *getName() const;
    int getWallsCounter() const;
    coordinates getPosition() const;

    void takeWall();
    void move(std::vector<std::pair<int, int>> possibleMovements);
    void placeWall(const int x, const int y, Direction direction, Board& board);
    bool needsToTakeInput();
};

#endif // PLAYER_H