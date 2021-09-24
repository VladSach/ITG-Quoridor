#include <iostream>
#include "Tile.h"

#define watch(x) std::cout << #x << " is " << x << std::endl

int main() {
    Tile myTile;
    myTile.setPosition(1, 3);

    myTile.setWall(upper);

    watch(myTile.getWall(left));
    watch(myTile.getWall(right));

    return 0;
}

