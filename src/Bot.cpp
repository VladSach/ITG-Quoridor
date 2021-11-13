#include "Bot.h"

Bot::Bot(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

void Bot::move(const int x, const int y) {
    m_X = x;
    m_Y = y;
}

void Bot::reduceWall() {    
    --m_WallsCounter;
}

bool Bot::needsToTakeInput() {
    return false;
}

const char* Bot::getName() const {
    return m_Name;
}

coordinates Bot::getPosition() const {
    return coordinates{m_X, m_Y};
}

int Bot::getWallsCounter() const {
    return m_WallsCounter;
}