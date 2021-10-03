#include "Game.h"
#include "View.h"
#include "Controller.h"
#include "Launcher.h"

#include <ctime> // time()
#include <cstdlib> // rand(), srand()

void single(const char* firstName, const char* secondName);
void multi(const char* firstName, const char* secondName);

int main() {
    srand(time(0));

    bool playAgain = true;

    do {
        Launcher launcher(&playAgain);

        char answer = launcher.menu();
        // std::cout << "You want to play alone or with a friend? S/m" << std::endl;
        // char answer = 's';
        // std::cin >> answer;

        if (answer == 's') single("Player", "Wally");
        else if (answer == 'm') multi("Player1", "Player2");
        else if (answer == 'e') playAgain = false;
        
        if (playAgain == true) answer = launcher.oneMore();
         

        // std::cout << "Want to play again? y/N" << std::endl;
        // std::cin >> answer;
        if (answer == 'y') playAgain = true;
        else playAgain = false;
        // std::cout << std::endl;

    } while (playAgain);

    return 0;
}

void single(const char* firstName, const char* secondName) {
    Player fp(mapSize/2, mapSize-1, firstName);
    Bot sp(mapSize/2, 0, secondName);

    Game game(fp, sp);
    View view(&game);
    Controller controller(&game, &view);
    controller.start();
}

void multi(const char* firstName, const char* secondName) {
    Player fp(mapSize/2, mapSize-1, firstName);
    Player sp(mapSize/2, 0, secondName);

    Game game(fp, sp);
    View view(&game);
    Controller controller(&game, &view);
    controller.start();
}