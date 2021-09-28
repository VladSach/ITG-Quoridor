#include "Bot.h"

Bot::Bot(const int x, const int y, const char* name) {
    m_X = x;
    m_Y = y;
    m_Name = name;
}

const char* Bot::getName() const {
    return m_Name;
}

// @param x,y returning values
int Bot::getPosition(int *const x, int *const y) const {
    *x = m_X;
    *y = m_Y;

    return 0;
}

int Bot::getWallsCounter() const {
    return m_WallsCounter;
}

void Bot::takeWall() {
    --m_WallsCounter;
}

void Bot::move(std::vector<std::pair<int, int>> possibleMovements) {
    int randomMove = rand() % possibleMovements.size();

    m_X = possibleMovements[randomMove].first;
    m_Y = possibleMovements[randomMove].second;
}

bool Bot::needsToTakeInput() {
    return false;
}