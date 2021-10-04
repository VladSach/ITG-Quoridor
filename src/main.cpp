#include "Launcher.h"
#include "ConfigReader.h"

#include <ctime> // time()
#include <cstdlib> // rand(), srand()

// TODO: Highlight current player name
// TODO: Slide show in launcher
// TODO: Input names in launcher
// TODO: Config file 
// TODO: show errors in GUI

    ConfigReader *configReader = ConfigReader::getInstance();

int main() {
    srand(time(0));
    
    Launcher launcher;

    do {
        launcher.mainMenu();
    } while (launcher.exitMenu());

    return 0;
}