#include "View.h"

View::View(Game *model) {
    m_model = model;
    m_model->addObserver(this);
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

void View::drawMap(Board board) {
    int x1, y1, x2, y2;
    m_model->getFirstPlayerPosition(&x1, &y1);
    m_model->getSecondPlayerPosition(&x2, &y2);

    char top[17] = {'A', 'S', 'B', 'T', 'C', 'U', 'D', 'V', 'E', 'W', 'F', 'X', 'G', 'Y', 'H', 'Z', 'I'};
    char cells[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    // std::string cells[9] = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};

    std::cout << "    ";
    for (int i = 0; i < mapSize; i++) {
        std::cout << top[i] << ' ';
    }
    std::cout << std::endl;
    
    std::cout << "    ";
    for (int i = 0; i < mapSize; i++) {
        std::cout << '-' << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < mapSize; i++) {
        if (i % 2 == 0)
        std::cout << i/2 + 1 << ' ' << '|' << ' ';
        else if (i % 2 == 1) 
        std::cout << i/2 + 1 << 'w' << '|' << ' ';

            for (int j = 0; j < mapSize; j++) {
                if (x1 == j && y1 == i) {
                    std::cout << 'W' << ' ';
                } else if (x2 == j && y2 == i) {
                    std::cout << 'B' << ' ';
                } else {
                    int c = board.getTile(j, i);
                    if (c == 0) std::cout << ' ';
                    else if (c == 1) std::cout << '.';
                    else if (c == 2) std::cout << '#';
                    std::cout << ' ';
                }
            }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector<std::pair<int, int>> moves = m_model->getPossibleMoves();

    std::cout << m_model->getCurrentPlayerName() << " Can move as this: ";
    for(auto e : moves) {
        std::cout << cells[e.first/2] << ' ' << e.second/2 + 1 << ' ';
        std::cout << '|' << ' ';
    }

    std::cout << std::endl;
    std::cout << std::endl;
}