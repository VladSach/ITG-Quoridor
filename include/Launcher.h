#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "Game.h"
#include "View.h"
#include "Controller.h"

class Launcher{

public:
    Launcher();
    ~Launcher() = default;
    
    void start();

    void singleWhite(const char* firstName, const char* secondName);
    void singleBlack(const char* firstName, const char* secondName);
};

#endif // LAUNCHER_H
