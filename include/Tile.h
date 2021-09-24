#ifndef TILE_H
#define TILE_H

enum { left  = 0x01,  // 0000 0001 
       upper = 0x02,  // 0000 0010
       lower = 0x04,  // 0000 0100
       right = 0x08,  // 0000 1000
       //lowMask = 0xFF // bitmask for storing last 4 bits
     };

class Tile { // 12 byte
private:
    int m_X; // 4 byte
    int m_Y; // 4 byte

    // m_Walls is a bitset
    unsigned char m_Walls; // 1 byte

public:
    Tile() = default;
    ~Tile() = default;

    bool getWall(unsigned char wall);
    int  getPosition(int *x, int *y);

    void setWall(unsigned char wall);
    void setPosition(int x, int y);
};

#endif