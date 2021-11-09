#ifndef UTILITY_H
#define UTILITY_H

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



#endif // UTILITY_H