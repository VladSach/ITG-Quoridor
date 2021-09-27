#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Game.h"

class Controller {
private:
    Game *m_model;

public:
    Controller(Game *model);
    ~Controller() = default;

    void start();
};

#endif // CONTROLLER_H