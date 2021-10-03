#ifndef LAUNCHER_H
#define LAUNCHER_H

// #include "Observer.h"
#include <SFML/Graphics.hpp>




class Launcher{
private:
    sf::Font font;

    sf::Text singePlayer;
    sf::Text multiplayer;
    sf::Text exit;
    sf::Text again;
    sf::Text yes;
    sf::Text no;

    bool *a;
    char answer;

    bool isMenu;
    bool isOneMore;
    int menuNum;

public:
    Launcher(bool *playAgain);
    ~Launcher() = default;
    
    char menu();
    char oneMore();
};

#endif // LAUNCHER_H
