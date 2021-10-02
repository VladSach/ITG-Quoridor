#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "Observer.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>



class Launcher: public Observer {
private:
    sf::Texture singlePlayerTexture;
    sf::Texture multiplayerTexture;
    sf::Texture exitTexture;

    sf::Sprite singePlayer;
    sf::Sprite multiplayer;
    sf::Sprite exit;

    sf::RenderWindow window;

    bool isMenu;
    int menuNum;

public:
    Launcher();
    ~Launcher() = default;

    virtual void update();
    
    void menu();
};

#endif // LAUNCHER_H
