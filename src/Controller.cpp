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
                coordinates coordCur = m_model->getCurrentPlayerPosition();
                int x = coordCur.x;
                int y = coordCur.y;

                sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                sf::Event event;
                while(window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window->close();
                    }
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (sf::IntRect(x * tileSize + wallsHolderSize, y * tileSize, tileSize, tileSize).contains(pixelPos.x, pixelPos.y)){
                            m_view->drawPossibleMoves();
                        } else {
                            m_model->makeTurn((pixelPos.x - wallsHolderSize)/ tileSize, pixelPos.y / tileSize);
                        }
                        for (unsigned int i = 0; i < m_model->getPossibleMoves().size(); i++) {
                            if (sf::IntRect(m_model->getPossibleMoves()[i].first - wallsHolderSize * tileSize, m_model->getPossibleMoves()[i].second * tileSize, tileSize, tileSize).contains(pixelPos.x, pixelPos.y)){
                                m_model->makeTurn(m_model->getPossibleMoves()[i].first - wallsHolderSize, m_model->getPossibleMoves()[i].second);
                            }
                        }
                    }
                }
            } else { 
                m_model->makeTurn(0, 0);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n\n";
        }
    }
}