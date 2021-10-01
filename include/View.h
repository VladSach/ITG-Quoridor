#ifndef VIEW_H
#define VIEW_H

#include "Game.h"
#include "Observer.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

const int SIZE = 9;
const int FIELD_SIZE = 510;
const int CELL_SIZE = 30;
const int ARRAY_SIZE = 17;

class View : public Observer {
private:
    Game *m_model;

    sf::RenderWindow m_window;

    sf::Texture mTexture;
    sf::Sprite mSprite;

    sf::Texture pTexture;
    sf::Sprite p1Sprite;
    sf::Sprite p2Sprite;

    sf::Texture wTexture;
    sf::Sprite wSprite;

    std::vector<std::pair<int,int>> moves;
public:
    View(Game *model);
    ~View() = default;

    virtual void update();

    sf::RenderWindow *getWindow();

    // ! Test function
    // ! Don't use it
    void drawMap(Board board);
    void drawPossibleMoves();
    void move(unsigned int i);
    void drawHorizontalWall(sf::Vector2i pixelPos);
    void drawVerticalWall(sf::Vector2i pixelPos);
};

#endif // VIEW_H