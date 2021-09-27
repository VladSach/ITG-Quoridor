#include "Controller.h"

Controller::Controller(Game *model) {
    m_model = model;
}

void Controller::start() {
    // TODO: add input handling and main game loop
    
    while (true) {
        m_model->placeWall(7, 3, vertical);
        m_model->movePlayer(8, 15);
        m_model->placeWall(9, 11, horizontal);
        m_model->movePlayer(10, 12);
        break;
    }
}