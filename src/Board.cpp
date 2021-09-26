#include "Board.h"

void Board::initBoard() {
    map = new char*[m_mapSize]{
        "01010101010101010",
        "11111111111111111",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010", 
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
        "01010101010101010",
    };

    // TODO: do this in a random way
    currentPlayer = &firstPlayer;

}
void Board::setWall(unsigned char wall) {
    // todo: add check for ability to place wall
    // todo: add check if player has any walls
    m_walls |= wall;
}

void Board::playerMove(Player *currentPlayer, PlayersChoice choice) {
    switch (choice) {
    case placeWall:
        currentPlayer->takeWall();
        break;

    case changePosition:

        break;
    
    default:
        break;
    }
}

// bool Tile::getWall(unsigned char wall) {
//     switch (wall) {
//     case leftWall:
//         return (m_Walls & leftWall) ? true : false;

//     case upperWall:
//         return (m_Walls & upperWall) ? true : false;

//     case lowerWall:
//         return (m_Walls & lowerWall) ? true : false;

//     case rightWall:
//         return (m_Walls & rightWall) ? true : false;
    
//     default:
//         return false;
//     }
// }