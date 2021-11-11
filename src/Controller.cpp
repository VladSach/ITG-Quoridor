#include "Controller.h"
#include <stdlib.h>
#include <string>

Controller::Controller(Game *model) {
    m_model = model;
    m_model->initGame();
}

void Controller::start() {
    int const mapSize = 9;
    while (true) {
        try {
            if (m_model->checkGameEnd() == true) break;
            
            if (m_model->getCurrentPlayerNeedsInput()) {
                std::string whatToDo, coordinates;

                std::cin >> whatToDo >> coordinates;

                if (whatToDo == "move"){
                    int x, y; 
                
                    char coordinateInLetter[mapSize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
                    for (int i = 0; i < mapSize; i++){
                        if (coordinateInLetter[i] == coordinates[0]) x = i*2;
                    }
                    
                    char yInChar = coordinates[1];
                    y = yInChar - '0';
                    y -= 1;
                    y *= 2;

                    m_model->makeTurn(x, y);
                }
                else if (whatToDo == "wall"){
                    int x, y;
                    char coordinateInLetter[mapSize - 1] = {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
                    for (int i = 0; i < mapSize - 1; i++){
                        if (coordinateInLetter[i] == coordinates[0]) x = i*2;
                    }
                    x += 1;
                    
                    char yInChar = coordinates[1];
                    y = yInChar - '0';
                    y -= 1;
                    y *= 2;
                    y += 1;

                    char wallOrientation = coordinates[2];
                    if (wallOrientation == 'h') x -= 1;
                    if (wallOrientation == 'v') y -= 1;

                    m_model->makeTurn(x, y);
                }
                else if (whatToDo == "stop") break;

                
            } else {
                m_model->makeTurn(0, 0);
            }
            
        } catch(const std::exception& e) {
            std::cerr << e.what() << "\n\n";
        }
    }
}