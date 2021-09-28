#include "Controller.h"

Controller::Controller(Game *model) {
    m_model = model;
}

void Controller::start() {
    // TODO: add input handling and main game loop

    multiPlayer();
    
}

void Controller::multiPlayer() {
    while (true) {
        try {
            if (m_model->checkGameEnd() == true) break;
            
            int x1, x2, y1, y2;
            m_model->getFirstPlayerPosition(&x1, &y1);
            m_model->getSecondPlayerPosition(&x2, &y2);
            std::cout << m_model->getFirstPlayerName() << " is on "
                      << x1 << ' ' << y1 << std::endl;
            std::cout << m_model->getSecondPlayerName() << " is on "
                      << x2 << ' ' << y2 << std::endl;

            std::cout << std::endl;

            std::cout << "Now is " << m_model->getCurrentPlayerName()
                      << "\'s move" << std::endl; 

            char move, dir;
            int x, y;
            std::cin >> move;
            switch (move) {
            case 'm':
                std::cin >> x >> y;
                m_model->movePlayer(x, y);
                continue;

            case 'w':
                std::cin >> x >> y >> dir;
                if (dir == 'v') m_model->placeWall(x, y, vertical);
                else if (dir == 'h') m_model->placeWall(x, y, horizontal);
                continue;

            case 'e':
                break;

            default:
                break;
            }

            break;
            
        } catch(const std::exception& e) {
            std::cerr << e.what() << "\n\n";
        }
    }

    if (m_model->checkGameEnd() == true) {
        std::cout << "Congrats " << m_model->getWinnerName() << std::endl;
    }
}