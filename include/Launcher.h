#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "Game.h"
#include "View.h"
#include "Controller.h"
#include <SFML/Graphics.hpp>

class Launcher{
private:
    sf::Font font;

    sf::Text singePlayerText;
    sf::Text multiplayerText;
    sf::Text exitText;
    sf::Text againText;
    sf::Text yesText;
    sf::Text noText;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Texture backgroundExitMenuTexture;
    sf::Sprite backgroundExitMenu;

    sf::Event event;

    // Window specifics
    static const unsigned int characterSize = 40;

    const sf::String launcherTitle = "Quoridor Launcher";
    const sf::Color backgroundColor = sf::Color(0x80, 0x80, 0x0);

    const int desktopWidth = sf::VideoMode::getDesktopMode().width;
    const int desktopHeight = sf::VideoMode::getDesktopMode().height;

    const sf::Vector2i centerWindow = {
        (desktopWidth / 2) - (desktopWidth / 4), 
        (desktopHeight / 2) - (desktopHeight / 4)
    };

    const sf::VideoMode windowSize = { windowWidth, windowHeight };

public:
    Launcher();
    ~Launcher() = default;
    
    void mainMenu();
    bool exitMenu();

    void singleplayer(const char* firstName, const char* secondName);
    void multiplayer(const char* firstName, const char* secondName);
};

#endif // LAUNCHER_H
