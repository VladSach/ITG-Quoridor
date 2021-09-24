#include <iostream>
#include "Board.h"

#define watch(x) std::cout << #x << " is " << x << std::endl

int main() {
    Tile myTile;
    myTile.setPosition(1, 3);

    myTile.setWall(upperWall);

    watch(myTile.getWall(leftWall));
    watch(myTile.getWall(rightWall));

    return 0;
}

