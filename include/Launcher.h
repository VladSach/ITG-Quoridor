#ifndef LAUNCHER_H
#define LAUNCHER_H

// #include "Observer.h"
#include <SFML/Graphics.hpp>




class Launcher{
private:
    // sf::Texture singlePlayerTexture;
    // sf::Texture multiplayerTexture;
    // sf::Texture exitTexture;
    // sf::Texture againTexture;
    // sf::Texture yesTexture;
    // sf::Texture noTexture;

    // sf::Sprite singePlayer;
    // sf::Sprite multiplayer;
    // sf::Sprite exit;
    // sf::Sprite again;
    // sf::Sprite yes;
    // sf::Sprite no;

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

    // virtual void update();
    
    char menu();
    char oneMore();
};

#endif // LAUNCHER_H
