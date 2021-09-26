#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

#include <iostream>



class Game {
private:
    Board board;

    Player firstPlayer;
    Player secondPlayer;
    Player *currentPlayer;
    Player *winner;

public:
    Game();
    ~Game() = default;

    void initGame();
    void switchCurrentPlayer();
    void movePlayer(const int x, const int y);
    void placeWall(const int x, const int y, Direction direction);

    // Test function
    void playGame(){
        int x, y;
        firstPlayer.getPosition(&x, &y);
        std::cout << x << ' ' << y << std::endl;
        for (int i = 0; i < mapSize; i++) {
            for (int j = 0; j < mapSize; j++) {
                if (i == y && j == x) {
                    std::cout << 'P' << ' ';
                } else {

                std::cout << board.getTile(i, j) << ' ';
                }
            }
            std::cout << std::endl;
        }

        movePlayer(8, 15);
        firstPlayer.getPosition(&x, &y);
        placeWall(9, 11, horizontal);
        std::cout << x << ' ' << y << std::endl;
        for (int i = 0; i < mapSize; i++) {
            for (int j = 0; j < mapSize; j++) {
                if (i == y && j == x) {
                    std::cout << 'P' << ' ';
                } else {

                std::cout << board.getTile(i, j) << ' ';
                }
            }
            std::cout << std::endl;
        }
    }

};

#endif // GAME_H