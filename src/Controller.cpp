#include "Controller.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

Controller::Controller(Game *model, View *view) {
    m_model = model;
    m_view = view;
    m_model->initGame();

    
}

void Controller::start() {
    sf::Window *window = m_view->getWindow();
    while (true) {
        try {
            if (m_model->checkGameEnd() == true) break;
            
            if (m_model->getCurrentPlayerNeedsInput()) {
                // int x, y;
                // std::cin >> x >> y;
                // if (x == 21) break;

                // m_model->makeTurn(x, y);
                while (window->isOpen()){
                    int x, y;
                    m_model->getCurrentPlayerPosition(&x, &y);

                    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                    sf::Event event;
                    while(window->pollEvent(event)){
                        if (event.type == sf::Event::Closed){
                            window->close();
                        }
                        if (event.type == sf::Event::MouseButtonPressed){
                            if (sf::IntRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE).contains(pixelPos.x, pixelPos.y)){
                                m_view->drawPossibleMoves();
                            } else{
                                m_model->makeTurn(pixelPos.x / CELL_SIZE, pixelPos.y / CELL_SIZE);
                            }
                            for (unsigned int i = 0; i < m_model->getPossibleMoves().size(); i++){
                                if (sf::IntRect(m_model->getPossibleMoves()[i].first * CELL_SIZE, m_model->getPossibleMoves()[i].second * CELL_SIZE, CELL_SIZE, CELL_SIZE).contains(pixelPos.x, pixelPos.y)){
                                    m_model->makeTurn(m_model->getPossibleMoves()[i].first, m_model->getPossibleMoves()[i].second);
                                    m_view->move(i);
                                }
                            }
                            

                            // try{
                            //     m_model->placeWall(pixelPos.x / CELL_SIZE, pixelPos.y / CELL_SIZE, horizontal);
                            //     m_view->drawHorizontalWall(pixelPos);
                            // } catch(const std::invalid_argument & e){
                            //     std::cout << e.what() << std::endl;
                            // }
                            // try{
                            //     m_model->placeWall(pixelPos.x / CELL_SIZE, pixelPos.y / CELL_SIZE, vertical);
                            //     m_view->drawVerticalWall(pixelPos);
                            // } catch(const std::invalid_argument & e){
                            //     std::cout << e.what() << std::endl;
                            // }
                        }
                    }
                }
            } else {
                m_model->makeTurn(0, 0);
            }
            
        } catch(const std::exception& e) {
            std::cerr << e.what() << "\n\n";
        }
    }
}