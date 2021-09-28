#include "Controller.h"

Controller::Controller(Game *model) {
    m_model = model;
    m_model->initGame();
}

void Controller::start() {
    while (true) {
        try {
            if (m_model->checkGameEnd() == true) break;
            
            if (m_model->getCurrentPlayerNeedsInput()) {
                int x, y;
                std::cin >> x >> y;
                if (x == 21) break;

                m_model->makeTurn(x, y);
            } else {
                m_model->makeTurn(0, 0);
            }
            
        } catch(const std::exception& e) {
            std::cerr << e.what() << "\n\n";
        }
    }
}