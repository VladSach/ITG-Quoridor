#ifndef PLAYER_H
#define PLAYER_H

enum Directions{
    left = 0, up, down, right
};

class Player {
private:
    int m_X;
    int m_Y;

    int m_WallsCounter = 10;

public:
    Player(int x, int y, int wallsAmount = 10);
    ~Player() = default;

    int getPosition(int *x, int *y);
    int getWallsCounter();

    void movePlayer(Directions direction);
    void takeWall();

};

#endif // PLAYER_H