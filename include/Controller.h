#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Game.h"
#include "View.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Controller {
private:
    Game *m_model;
    View *m_view;

public:
    Controller(Game *model, View *view);
    ~Controller() = default;

    void start();
};

#endif // CONTROLLER_H