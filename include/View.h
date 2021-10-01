#ifndef VIEW_H
#define VIEW_H

#include "Game.h"
#include "Observer.h"
#include <SFML/Graphics.hpp>

const int CELL_SIZE = 30; // Board is 510x510

class View : public Observer {
private:
    Game *m_model;

    sf::RenderWindow m_Window;

    sf::Texture boardTexture;
    sf::Sprite boardSprite;

    sf::Texture playerTexture;
    sf::Sprite player1Sprite;
    sf::Sprite player2Sprite;

    std::vector<std::pair<int,int>> moves;
public:
    View(Game *model);
    ~View() = default;

    virtual void update();

    sf::RenderWindow *getWindow();

    void drawMap(Board board);
    void drawPossibleMoves();
};

#endif // VIEW_H