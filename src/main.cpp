#include "Game.h"
#include "View.h"
#include "Controller.h"

int main() {
    Game game;
    View view(&game);
    Controller controller(&game);
    controller.start();

    return 0;
}

