#include "View.h"

View::View(Game *model) {
    m_model = model;
    m_model->addObserver(this);
}

void View::update() {
    // TODO: Here goes the grahics

    drawMap(m_model->getBoard());

}

void View::drawMap(Board board) {
    int x1, y1, x2, y2;
    m_model->getFirstPlayerPosition(&x1, &y1);
    m_model->getSecondPlayerPosition(&x2, &y2);

    std::cout << "    ";
    for (int i = 0; i < mapSize; i++) {
        if (i < 10)
        std::cout << i << ' ';
        else if (i >= 10) 
        std::cout << i-10 << ' ';
    }
    std::cout << std::endl;
    
    std::cout << "    ";
    for (int i = 0; i < mapSize; i++) {
        std::cout << '-' << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < mapSize; i++) {
        if (i < 10)
        std::cout << i << ' ' << '|' << ' ';
        else if (i >= 10) 
        std::cout << i << '|' << ' ';

            for (int j = 0; j < mapSize; j++) {
                if (x1 == j && y1 == i) {
                    std::cout << 'P' << ' ';
                } else if (x2 == j && y2 == i) {
                    std::cout << 'S' << ' ';
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

}