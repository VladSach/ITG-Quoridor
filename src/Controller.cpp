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
    while (window->isOpen()){
        try {
            if (m_model->checkGameEnd() == true) break;
            if (m_model->getCurrentPlayerNeedsInput()) {
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
                            }
                        }
                    }
                }
            } else { m_model->makeTurn(0, 0); }
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n\n";
        }
    }
}