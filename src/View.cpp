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
                case 2:
                    wSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                    wSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                    m_window.draw(wSprite);
                    break;
                case 1:
                    mSprite.setTextureRect(sf::IntRect(50, 0, CELL_SIZE, CELL_SIZE));
                    break;
                
                case 0:
                    mSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                    break;
                }
                mSprite.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                m_window.draw(mSprite);
            }   
        }
    p1Sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
    p1Sprite.setPosition(x1 * CELL_SIZE, y1 * CELL_SIZE);
    m_window.draw(p1Sprite);

    p2Sprite.setTextureRect(sf::IntRect(30, 0, CELL_SIZE, CELL_SIZE));
    p2Sprite.setPosition(x2 * CELL_SIZE, y2 * CELL_SIZE);
    m_window.draw(p2Sprite);

    // while (window.isOpen()){

    //     sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	// 	// sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

    //     sf::Event event;
    //     while (window.pollEvent(event)){
    //         if (event.type == sf::Event::Closed){
    //             window.close();
    //         }
    //         if (event.type == sf::Event::MouseButtonPressed){
    //             if (sf::IntRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE).contains(pixelPos.x, pixelPos.y)){
    //                 moves = m_model->getPossibleMoves();                    
    //                 for (unsigned int i = 0; i < moves.size(); i++){
    //                     mSprite.setTextureRect(sf::IntRect(100, 0, CELL_SIZE, CELL_SIZE));
    //                     mSprite.setPosition(moves[i].first * CELL_SIZE, moves[i].second * CELL_SIZE);
    //                     window.draw(mSprite);
    //                 }
    //             }
    //             for (unsigned int i = 0; i < moves.size(); i++){
    //                 if (sf::IntRect(moves[i].first * CELL_SIZE, moves[i].second * CELL_SIZE, CELL_SIZE, CELL_SIZE).contains(pixelPos.x, pixelPos.y)){
    //                     p1Sprite.move(sf::Vector2f(moves[i].first * CELL_SIZE - p1Sprite.getPosition().x , moves[i].second * CELL_SIZE - p1Sprite.getPosition().y));
    //                     window.draw(p1Sprite);
    //                     m_model->makeTurn(moves[i].first, moves[i].second);
    //                     for (unsigned int j = 0; j < moves.size(); j++){
    //                         mSprite.setTextureRect(sf::IntRect(50, 0, CELL_SIZE, CELL_SIZE));
    //                         mSprite.setPosition(moves[j].first * CELL_SIZE, moves[j].second * CELL_SIZE);
    //                         window.draw(mSprite);
    //                     }
    //                     moves.clear();
    //                 }
                
    //             }
    //             try{
    //                 m_model->placeWall(pixelPos.x / CELL_SIZE, pixelPos.y / CELL_SIZE, horizontal);
    //                 wSprite.setTextureRect(sf::IntRect(0, 0, 90, CELL_SIZE));
    //                 wSprite.setPosition((pixelPos.x / CELL_SIZE) * CELL_SIZE, (pixelPos.y / CELL_SIZE) * CELL_SIZE);
    //                 window.draw(wSprite);
    //             } catch(const std::invalid_argument & e){
    //                 std::cout << e.what() << std::endl;
    //             }
    //             try{
    //                 m_model->placeWall(pixelPos.x / CELL_SIZE, pixelPos.y / CELL_SIZE, vertical);
    //                 wSprite.setTextureRect(sf::IntRect(90, 0, CELL_SIZE, 90));
    //                 wSprite.setPosition((pixelPos.x / CELL_SIZE) * CELL_SIZE, (pixelPos.y / CELL_SIZE) * CELL_SIZE);
    //                 window.draw(wSprite);
    //             } catch(const std::invalid_argument & e){
    //                 std::cout << e.what() << std::endl;
    //             }
    //         }
    //     }
    // }
}

void View::drawPossibleMoves(){
    moves = m_model->getPossibleMoves();                    
    for (unsigned int i = 0; i < moves.size(); i++){
        std::cout << moves[i].first << " " << moves[i].second << std::endl;
        mSprite.setTextureRect(sf::IntRect(100, 0, CELL_SIZE, CELL_SIZE));
        mSprite.setPosition(moves[i].first * CELL_SIZE, moves[i].second * CELL_SIZE);
        m_window.draw(mSprite);
    }
}

void View::move(unsigned int i){
    moves = m_model->getPossibleMoves();    
    p1Sprite.move(sf::Vector2f(moves[i].first * CELL_SIZE - p1Sprite.getPosition().x , moves[i].second * CELL_SIZE - p1Sprite.getPosition().y));
    m_window.draw(p1Sprite);
    for (unsigned int j = 0; j < moves.size(); j++){
        mSprite.setTextureRect(sf::IntRect(50, 0, CELL_SIZE, CELL_SIZE));
        mSprite.setPosition(moves[j].first * CELL_SIZE, moves[j].second * CELL_SIZE);
        m_window.draw(mSprite);
    }
    moves.clear();
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