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

    coordinates move = m_model->getLastMove();
    coordinates otherP = m_model->getOtherPlayerPosition();

    char coordinateInLetter[mapSize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    char coordinateInLetterWalls[mapSize - 1] = {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    if (move.x % 2 == 0 && move.y % 2 == 0){
        if (((otherP.x - move.x <= 2) && (otherP.x - move.x >= -2)) &&
         ((otherP.y - move.y <= 2) && (otherP.y - move.y >= -2))){
            std::cout << "move " << coordinateInLetter[move.x/2] << move.y/2 + 1 << std::endl;
            
        }
        else {
            std::cout << "jump " << coordinateInLetter[move.x/2] << move.y/2 + 1 << std::endl;
        }
    }
    else if (move.x % 2 == 0 && move.y % 2 == 1){
        std::cout << "wall " << coordinateInLetterWalls[move.x/2] << move.y/2 + 1 << "h" << std::endl;
    }
    else if (move.x % 2 == 1 && move.y % 2 == 0){
        std::cout << "wall " << coordinateInLetterWalls[move.x/2] << move.y/2 + 1 << "v" << std::endl;
    }

}