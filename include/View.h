#ifndef VIEW_H
#define VIEW_H

#include "Game.h"
#include "Observer.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

const int SIZE = 9;
const int FIELD_SIZE = 530;
const int CELL_SIZE = 50;
const int ARRAY_SIZE = 17;

class View : public Observer {
private:
    Game *m_model;
    sf::Texture mTexture;
    sf::Sprite mSprite;

public:
    View(Game *model);
    ~View() = default;

    virtual void update();

    // ! Test function
    // ! Don't use it
    void drawMap(Board board);
};

#endif // VIEW_H