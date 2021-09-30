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
    int x1, y1, x2, y2;
    m_model->getFirstPlayerPosition(&x1, &y1);  
    m_model->getSecondPlayerPosition(&x2, &y2);

    // sf::String TileMap[] = 

    sf::RenderWindow window(sf::VideoMode({510, 510}), "Quoridor");

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased){}
        }

        window.clear(sf::Color(0x80, 0x80, 0x0));

        for(float i = 0; i < ARRAY_SIZE; i++){
            for(float j = 0; j < ARRAY_SIZE; j++){
                switch (board.getTile(i,j))
                {
                case 1:
                    mSprite.setTextureRect(sf::IntRect(50, 0, 30, 30));
                    break;
                
                case 0:
                    mSprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
                    break;
                }
                // sf::RectangleShape shape1(sf::Vector2f(50, 50));
                // shape1.setPosition({i * 70, j * 70});
                // shape1.setFillColor(sf::Color(0x80, 0x0, 0x0));
                // window.draw(shape1);
                mSprite.setPosition(j * 30, i * 30);
                window.draw(mSprite);
            }
        }
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