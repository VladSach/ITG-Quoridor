#ifndef VIEW_H
#define VIEW_H

#include "Game.h"
#include "Observer.h"
#include <SFML/Graphics.hpp>

enum {
    tileSize = 30,
    wallsHolderSize = 110,
    windowWidth = tileSize*mapSize + wallsHolderSize*2, // 730
    windowHeight = tileSize*mapSize // 510
};

class View : public Observer {
private:
    Game *m_model;

    sf::RenderWindow m_Window;

    sf::Texture boardTexture;
    sf::Sprite boardSprite;

    sf::Texture playerTexture;
    sf::Sprite player1Sprite;
    sf::Sprite player2Sprite;

    sf::Font font;
    sf::Text player1Name;
    sf::Text player2Name;

    std::vector<std::pair<int,int>> moves;
    
    // Window specifics
    const sf::String gameTitle = "Quoridor";
    const int desktopWidth = sf::VideoMode::getDesktopMode().width;
    const int desktopHeight = sf::VideoMode::getDesktopMode().height;

    const sf::Vector2i centerWindow = {
        (desktopWidth / 2) - (desktopWidth / 4),
        (desktopHeight / 2) - (desktopHeight / 4) };

    const sf::VideoMode windowSize = { windowWidth, windowHeight };

public:
    View(Game *model);
    ~View() = default;

    virtual void update();

    sf::RenderWindow *getWindow();

    void drawMap(Board board);
    void drawPossibleMoves();
};

#endif // VIEW_H