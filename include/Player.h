#ifndef PLAYER_H
#define PLAYER_H

enum PlayerDirection{
    left = 0, up, down, right,
    upper_left, upper_right,
    lower_left, lower_right
};

class Player {
private:
    int m_X;
    int m_Y;

    // I guess restrict in 25 symbols is ok
    const char *m_Name;
    
    // ? Give ability to decide Walls Amount before game started?
    int m_WallsCounter = 10;

public:
    Player(const int x, const int y, const char *name);
    ~Player() = default;

    const char *getName();
    int getWallsCounter();
    int getPosition(int *x, int *y);

    void takeWall();
    void movePlayer(PlayerDirection direction);
    void doubleMove(PlayerDirection direction);
    void diagonalMove(PlayerDirection direction);
    
    // rhs means "right hand side"
    bool operator == (const Player& rhs) const {
        return
               this->m_X == rhs.m_X
            && this->m_Y == rhs.m_Y
            && this->m_Name == rhs.m_Name;
    }

};

#endif // PLAYER_H