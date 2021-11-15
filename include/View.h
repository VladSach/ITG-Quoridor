#ifndef VIEW_H
#define VIEW_H

#include "Game.h"
#include "Observer.h"
#include "utility.h"

#include <iostream>

class View : public Observer {
private:
    Game *m_model;

public:
    View(Game *model);
    ~View() = default;

    virtual void update();

    // ! Test function
    // ! Don't use it
};

#endif // VIEW_H