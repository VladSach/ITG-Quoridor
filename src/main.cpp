#include "Game.h"
#include "View.h"
#include "Controller.h"

#include <ctime> // time()
#include <cstdlib> // rand(), srand()

int main() {
    srand(time(0));

    std::cout << "You want to play agains player or bot?" << std::endl;

    Player fp(mapSize/2, mapSize-1, "John");
    Player sp(mapSize/2, 0, "Bot");

    Game game(fp, sp);
    View view(&game);
    Controller controller(&game);
    controller.start();

    return 0;
}

