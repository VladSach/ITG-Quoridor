#include "View.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


View::View(Game *model) {
    m_model = model;
    m_model->addObserver(this);

    window.create(sf::VideoMode({510, 510}), "Quoridor");

    window.clear(sf::Color(0x80, 0x80, 0x0));

    mTexture.loadFromFile("./media/map.png");
    mTexture.setSmooth(true);
    mSprite.setTexture(mTexture);

    pTexture.loadFromFile("./media/players2.png");
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

    window.display();
}


// void View::draw(sf::RenderTarget& target, sf::RenderStates states) const
// {
//     states.transform *= getTransform();
//     sf::Color color = sf::Color(200, 100, 200);

//     sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
//     shape.setOutlineThickness(2.f);
//     shape.setOutlineColor(color);
//     spahe.setFillColor(sf::Color::Transparent);
    
//     for (unsigned int i = 0; i < ARRAY_SIZE; i++);{
//         sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
//         shape.setPosition(position);
//         target.draw(shape, states);
//     }
// }

void View::drawMap(Board board) {
    int x1, y1, x2, y2, x, y;
    m_model->getFirstPlayerPosition(&x1, &y1);  
    m_model->getSecondPlayerPosition(&x2, &y2);
    m_model->getCurrentPlayerPosition(&x, &y);

    std::vector<std::pair<int,int>> moves;

    for(int i = 0; i < ARRAY_SIZE; i++){
            for(int j = 0; j < ARRAY_SIZE; j++){
                switch (board.getTile(i,j))
                {
                case 1:
                    mSprite.setTextureRect(sf::IntRect(50, 0, CELL_SIZE, CELL_SIZE));
                    break;
                
                case 0:
                    mSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                    break;
                }
                mSprite.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                window.draw(mSprite);
            }   
        }
    p1Sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
    p1Sprite.setPosition(x1 * CELL_SIZE, y1 * CELL_SIZE);
    window.draw(p1Sprite);

    p2Sprite.setTextureRect(sf::IntRect(30, 0, CELL_SIZE, CELL_SIZE));
    p2Sprite.setPosition(x2 * CELL_SIZE, y2 * CELL_SIZE);
    window.draw(p2Sprite);

    while (window.isOpen()){

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		// sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if (sf::IntRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE).contains(pixelPos.x, pixelPos.y)){
                    moves = m_model->getPossibleMoves();                    
                    // if (currentPlayerSprite == p1Sprite){
                    //     currentPlayerSprite = p2Sprite;
                    // } else currentPlayerSprite = p1Sprite;
                    for (unsigned int i = 0; i < moves.size(); i++){
                        mSprite.setTextureRect(sf::IntRect(100, 0, CELL_SIZE, CELL_SIZE));
                        mSprite.setPosition(moves[i].first * CELL_SIZE, moves[i].second * CELL_SIZE);
                        window.draw(mSprite);
                    }
                }
                for (unsigned int i = 0; i < moves.size(); i++){
                    if (sf::IntRect(moves[i].first * CELL_SIZE, moves[i].second * CELL_SIZE, CELL_SIZE, CELL_SIZE).contains(pixelPos.x, pixelPos.y)){
                        p1Sprite.move(sf::Vector2f(moves[i].first * CELL_SIZE - p1Sprite.getPosition().x , moves[i].second * CELL_SIZE - p1Sprite.getPosition().y));
                        window.draw(p1Sprite);
                        m_model->makeTurn(moves[i].first, moves[i].second);
                        for (unsigned int j = 0; j < moves.size(); j++){
                            mSprite.setTextureRect(sf::IntRect(50, 0, CELL_SIZE, CELL_SIZE));
                            mSprite.setPosition(moves[j].first * CELL_SIZE, moves[j].second * CELL_SIZE);
                            window.draw(mSprite);
                        }
                        moves.clear();
                    }
                
                }
                try{
                    m_model->placeWall(pixelPos.x / CELL_SIZE, pixelPos.y / CELL_SIZE, horizontal);
                    wSprite.setTextureRect(sf::IntRect(0, 0, 90, CELL_SIZE));
                    wSprite.setPosition((pixelPos.x / CELL_SIZE) * CELL_SIZE, (pixelPos.y / CELL_SIZE) * CELL_SIZE);
                    window.draw(wSprite);
                } catch(const std::invalid_argument & e){
                    std::cout << e.what() << std::endl;
                }
                try{
                    m_model->placeWall(pixelPos.x / CELL_SIZE, pixelPos.y / CELL_SIZE, vertical);
                    wSprite.setTextureRect(sf::IntRect(90, 0, CELL_SIZE, 90));
                    wSprite.setPosition((pixelPos.x / CELL_SIZE) * CELL_SIZE, (pixelPos.y / CELL_SIZE) * CELL_SIZE);
                    window.draw(wSprite);
                } catch(const std::invalid_argument & e){
                    std::cout << e.what() << std::endl;
                }
            }
        }

        // sf::RectangleShape player1(sf::Vector2i(30, 30));
        // player1.setPosition({x1 * 30, y1 * 30});
        // player1.setFillColor(sf::Color(0x80, 0x80, 0x0));
        // window.draw(player1);

        // sf::RectangleShape player2(sf::Vector2i(30, 30));
        // player2.setPosition({x2 * 30, y2 * 30});
        // player2.setFillColor(sf::Color(0x0, 0x0, 0xFF));
        // window.draw(player2);

    }

    // std::cout << "    ";
    // for (int i = 0; i < mapSize; i++) {
    //     if (i < 10)
    //     std::cout << i << ' ';
    //     else if (i >= 10) 
    //     std::cout << i-10 << ' ';
    // }
    // std::cout << std::endl;
    
    // std::cout << "    ";
    // for (int i = 0; i < mapSize; i++) {
    //     std::cout << '-' << ' ';
    // }
    // std::cout << std::endl;

    // for (int i = 0; i < mapSize; i++) {
    //     if (i < 10)
    //     std::cout << i << ' ' << '|' << ' ';
    //     else if (i >= 10) 
    //     std::cout << i << '|' << ' ';

    //         for (int j = 0; j < mapSize; j++) {
    //             if (x1 == j && y1 == i) {
    //                 std::cout << 'P' << ' ';
    //             } else if (x2 == j && y2 == i) {
    //                 std::cout << 'S' << ' ';
    //             } else {
    //                 int c = board.getTile(j, i);
    //                 if (c == 0) std::cout << ' ';
    //                 else if (c == 1) std::cout << '.';
    //                 else if (c == 2) std::cout << '#';
    //                 std::cout << ' ';
    //             }
    //         }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    // std::vector<std::pair<int, int>> moves = m_model->getPossibleMoves();

    // std::cout << m_model->getCurrentPlayerName() << " Can move as this: ";
    // for(auto e : moves) {
    //     std::cout << e.first << ' ' << e.second << ' ';
    //     std::cout << '|' << ' ';
    // }

    // std::cout << std::endl;
    // std::cout << std::endl;
}
