#include "Bot.h"

Bot::Bot(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;

    m_EndY = (y == 0) ? mapSize-1 : 0;
}

void Bot::move(const int x, const int y) {
    m_X = x;
    m_Y = y;
}

void Bot::reduceWall() {    
    --m_WallsCounter;
}

void Bot::returnWall() {
    ++m_WallsCounter;
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

int Bot::getEndY() const {
    return m_EndY;
}