#include "View.h"

View::View(Game *model) {
    m_model = model;
    m_model->addObserver(this);
}

void View::update() {
    // if (m_model->checkGameEnd() == true) {
    //     std::cout << "Congrats " << m_model->getWinnerName() << std::endl;
    // } else {
    //     std::cout << "Now is " << m_model->getCurrentPlayerName()
    //             << "\'s move" << std::endl; 
    // }
    // std::cout << std::endl;

}