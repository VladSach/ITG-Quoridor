#include "View.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


View::View(Game *model) {
    m_model = model;
    m_model->addObserver(this);

    m_window.create(sf::VideoMode({510, 510}), "Quoridor");

    m_window.clear(sf::Color(0x80, 0x80, 0x0));

    mTexture.loadFromFile("./media/map.png");
    mTexture.setSmooth(true);
    mSprite.setTexture(mTexture);

    pTexture.loadFromFile("./media/players.png");
    pTexture.setSmooth(true);
    p1Sprite.setTexture(pTexture);
    p2Sprite.setTexture(pTexture);

    wTexture.loadFromFile("./media/walls.png");
    wTexture.setSmooth(true);
    wSprite.setTexture(wTexture);
}

void View::update() {
    if (m_model->checkGameEnd() == true) {
        std::cout << "Congrats " << m_model->getWinnerName() << std::endl;
    } else {
        std::cout << "Now is " << m_model->getCurrentPlayerName()
                << "\'s move" << std::endl; 
    }
    std::cout << std::endl;

    drawMap(m_model->getBoard());

    m_window.display();
}

void View::drawMap(Board board) {
    int x1, y1, x2, y2, x, y;
    m_model->getFirstPlayerPosition(&x1, &y1);  
    m_model->getSecondPlayerPosition(&x2, &y2);
    m_model->getCurrentPlayerPosition(&x, &y);

    for(int i = 0; i < ARRAY_SIZE; i++){
            for(int j = 0; j < ARRAY_SIZE; j++){
                switch (board.getTile(i,j))
                {
                case wall:
                    wSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                    wSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                    m_window.draw(wSprite);
                    break;
                case tile:
                    mSprite.setTextureRect(sf::IntRect(50, 0, CELL_SIZE, CELL_SIZE));
                    mSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                    m_window.draw(mSprite);
                    break;
                
                case empty:
                    mSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                    mSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                    m_window.draw(mSprite);
                    break;
                }

            }   
        }
    p1Sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
    p1Sprite.setPosition(x1 * CELL_SIZE, y1 * CELL_SIZE);
    m_window.draw(p1Sprite);

    p2Sprite.setTextureRect(sf::IntRect(30, 0, CELL_SIZE, CELL_SIZE));
    p2Sprite.setPosition(x2 * CELL_SIZE, y2 * CELL_SIZE);
    m_window.draw(p2Sprite);

    
}

void View::drawPossibleMoves(){
    moves = m_model->getPossibleMoves();                    
    for (unsigned int i = 0; i < moves.size(); i++){
        mSprite.setTextureRect(sf::IntRect(100, 0, CELL_SIZE, CELL_SIZE));
        mSprite.setPosition(moves[i].first * CELL_SIZE, moves[i].second * CELL_SIZE);
        m_window.draw(mSprite);
    }
    m_window.display();
}

sf::RenderWindow *View::getWindow(){
    return &m_window;
}

void View::drawHorizontalWall(sf::Vector2i pixelPos){
    wSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
    wSprite.setPosition((pixelPos.x / CELL_SIZE) * CELL_SIZE, (pixelPos.y / CELL_SIZE) * CELL_SIZE);
    m_window.draw(wSprite);
}

void View::drawVerticalWall(sf::Vector2i pixelPos){
    wSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
    wSprite.setPosition((pixelPos.x / CELL_SIZE) * CELL_SIZE, (pixelPos.y / CELL_SIZE) * CELL_SIZE);
    m_window.draw(wSprite);
}