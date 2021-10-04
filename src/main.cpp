#include "Launcher.h"

#include <ctime> // time()
#include <cstdlib> // rand(), srand()

// TODO: Slide show in launcher
// TODO: Input names in launcher
// TODO: Config file 
// TODO: show errors in GUI

int main() {
    srand(time(0));
    
    Launcher launcher;

    do {
        launcher.mainMenu();
    } while (launcher.exitMenu());

    return 0;
}