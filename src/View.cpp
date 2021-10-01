#include "View.h"

View::View(Game *model) {
    m_model = model;
    m_model->addObserver(this);

    unsigned int desktopWidth = sf::VideoMode::getDesktopMode().width;
    unsigned int desktopHeight = sf::VideoMode::getDesktopMode().height;
    sf::Vector2i centerWindow((desktopWidth / 2) - (desktopWidth / 4),
                              (desktopHeight / 2) - (desktopHeight / 4));

    m_Window.create(sf::VideoMode({CELL_SIZE*mapSize, CELL_SIZE*mapSize}), 
                    "Quoridor",
                    sf::Style::Titlebar |
                    sf::Style::Close);

    m_Window.setPosition(centerWindow);
    m_Window.clear(sf::Color::Black);

    boardTexture.loadFromFile("./media/map.png");
    boardTexture.setSmooth(true);
    boardSprite.setTexture(boardTexture);

    playerTexture.loadFromFile("./media/players.png");
    playerTexture.setSmooth(true);
    player1Sprite.setTexture(playerTexture);
    player2Sprite.setTexture(playerTexture);
}

void View::update() {
    // ! Add this to Launcher
    if (m_model->checkGameEnd() == true) {
        std::cout << "Congrats " << m_model->getWinnerName() << std::endl;
    }

    drawMap(m_model->getBoard());
    m_Window.display();
}

void View::drawMap(Board board) {
    int x, y, x1, y1, x2, y2;
    m_model->getCurrentPlayerPosition(&x, &y);
    m_model->getFirstPlayerPosition(&x1, &y1);  
    m_model->getSecondPlayerPosition(&x2, &y2);

    for(int i = 0; i < mapSize; i++){
        for(int j = 0; j < mapSize; j++){
            switch (board.getTile(i,j)) {
            case empty:
                boardSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                break;

            case tile:
                boardSprite.setTextureRect(sf::IntRect(50, 0, CELL_SIZE, CELL_SIZE));
                break;
            
            case wall:
                boardSprite.setTextureRect(sf::IntRect(0, 50, CELL_SIZE, CELL_SIZE));
                break;
            }

            boardSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            m_Window.draw(boardSprite);
        }   
    }

    player1Sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
    player1Sprite.setPosition(x1 * CELL_SIZE, y1 * CELL_SIZE);
    m_Window.draw(player1Sprite);

    player2Sprite.setTextureRect(sf::IntRect(30, 0, CELL_SIZE, CELL_SIZE));
    player2Sprite.setPosition(x2 * CELL_SIZE, y2 * CELL_SIZE);
    m_Window.draw(player2Sprite);
}

void View::drawPossibleMoves(){
    moves = m_model->getPossibleMoves();                    
    for (unsigned int i = 0; i < moves.size(); i++){
        boardSprite.setTextureRect(sf::IntRect(100, 0, CELL_SIZE, CELL_SIZE));
        boardSprite.setPosition(moves[i].first * CELL_SIZE, moves[i].second * CELL_SIZE);
        m_Window.draw(boardSprite);
    }
    m_Window.display();
}

sf::RenderWindow *View::getWindow(){
    return &m_Window;
}