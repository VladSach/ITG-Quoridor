#ifndef PLAYER_H
#define PLAYER_H

enum PlayerDirection{
    left = 0, up, down, right,
    upper_left, upper_right,
    lower_left, lower_right,
    last
};

class IPlayer {
private:
    int m_X;
    int m_Y;
    const char* m_Name;

public:
    virtual ~IPlayer() {};

    virtual const char *getName() = 0;
    virtual int getWallsCounter() = 0;
    virtual int getPosition(int *x, int *y) = 0;

    virtual void takeWall() = 0;
    virtual void movePlayer(PlayerDirection) = 0;
    virtual void doubleMove(PlayerDirection) = 0;
    virtual void diagonalMove(PlayerDirection) = 0;

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
    
    // ? Give ability to decide Walls Amount before game started?
    int m_WallsCounter = 10;

public:
    Player(const int x, const int y, const char *name);
    Player() = default;
    ~Player() = default;

    const char *getName();
    int getWallsCounter();
    int getPosition(int *x, int *y);

    void takeWall();
    void movePlayer(PlayerDirection direction);
    void doubleMove(PlayerDirection direction);
    void diagonalMove(PlayerDirection direction);
};

#endif // PLAYER_H