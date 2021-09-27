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
    for (int i = 0; i < mapSize; i++) {
            for (int j = 0; j < mapSize; j++) {
                if (x1 == j && y1 == i) {
                    std::cout << 'P' << ' ';
                } else if (x2 == j && y2 == i) {
                    std::cout << 'S' << ' ';
                } else {
                    std::cout << board.getTile(i, j) << ' ';
                }
            }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}