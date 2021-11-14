#ifndef UTILITY_H
#define UTILITY_H

enum {
    WallsAmount = 10,
    mapSize = 17
};

enum Field {
    empty = 0,
    tile  = 1,
    wall  = 2
};

enum Direction {
    horizontal = 0,
    vertical
};

struct coordinates {
    int x;
    int y;
};

// Squared distance between two points
inline unsigned int distanceBetweenTwoPoints(coordinates start, coordinates end) {
    const int distanceSq = ((end.x - start.x)*(end.x - start.x)) + 
                           ((end.y - start.y)*(end.y - start.y));

    const int mask = distanceSq >> (sizeof(int) * __CHAR_BIT__ - 1);
    unsigned int distance = (distanceSq + mask) ^ mask;
    return distance; 
}

inline unsigned int absQ(int number) {
    // * No need for cmath library
    // * http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
    const int mask = number >> (sizeof(int) * __CHAR_BIT__ - 1);
    unsigned int absNumber = (number + mask) ^ mask;
    return absNumber;
}

#endif // UTILITY_H