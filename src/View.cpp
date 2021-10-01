#include "View.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


View::View(Game *model) {
    m_model = model;
    m_model->addObserver(this);

    mTexture.loadFromFile("./media/map.png");
    mTexture.setSmooth(true);
    mSprite.setTexture(mTexture);
    pTexture.loadFromFile("./media/players2.png");
    pTexture.setSmooth(true);
    pSprite.setTexture(pTexture);
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

    // sf::String TileMap[] = 

    sf::RenderWindow window(sf::VideoMode({510, 510}), "Quoridor");

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if (sf::IntRect(x, y, CELL_SIZE, CELL_SIZE).contains(sf::Mouse::getPosition(window))){
                    moves = m_model->getPossibleMoves();
                    std::cout << "That's ok" << std::endl;
                    for (unsigned int i = 0; i < moves.size(); i++){
                        mSprite.setTextureRect(sf::IntRect(100, 0, CELL_SIZE, CELL_SIZE));
                        mSprite.setPosition(moves[i].first * CELL_SIZE, moves[i].second * CELL_SIZE);
                        window.draw(mSprite);
                    }
                }
            }
        }

        window.clear(sf::Color(0x80, 0x80, 0x0));

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
        pSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
        pSprite.setPosition(x1 * CELL_SIZE, y1 * CELL_SIZE);
        window.draw(pSprite);

        pSprite.setTextureRect(sf::IntRect(30, 0, CELL_SIZE, CELL_SIZE));
        pSprite.setPosition(x2 * CELL_SIZE, y2 * CELL_SIZE);
        window.draw(pSprite);
        // sf::RectangleShape player1(sf::Vector2i(30, 30));
        // player1.setPosition({x1 * 30, y1 * 30});
        // player1.setFillColor(sf::Color(0x80, 0x80, 0x0));
        // window.draw(player1);

        // sf::RectangleShape player2(sf::Vector2i(30, 30));
        // player2.setPosition({x2 * 30, y2 * 30});
        // player2.setFillColor(sf::Color(0x0, 0x0, 0xFF));
        // window.draw(player2);

        window.display();
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
