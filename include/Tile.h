#ifndef TILE_H
#define TILE_H

enum { 
    leftWall  = 0x01,  // 0000 0001 
    upperWall = 0x02,  // 0000 0010
    lowerWall = 0x04,  // 0000 0100
    rightWall = 0x08,  // 0000 1000
    //lowMask = 0xFF // bitmask for storing last 4 bits
};

class Tile { // 12 byte
private:
    int m_X; // 4 byte
    int m_Y; // 4 byte

    // m_Walls is a bitset
    unsigned char m_Walls = 0x0; // 1 byte

public:
    Tile()  = default;
    ~Tile() = default;

    bool getWall(unsigned char wall);
    int  getPosition(int *x, int *y);

    void setWall(unsigned char wall);
    void setPosition(int x, int y);
};

#endif // TILE_H