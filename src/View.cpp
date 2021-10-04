#include "View.h"

View::View(Game *model): player1Name("", font, 30), player2Name("", font, 30), currentPlayerName("", font, 30) {
    m_model = model;
    m_model->addObserver(this);

    m_Window.create(windowSize, gameTitle, 
                    sf::Style::Titlebar | 
                    sf::Style::Close);

    m_Window.setPosition(centerWindow);
    m_Window.clear(sf::Color::White);

    // Load textures
    boardTexture.loadFromFile("./media/map.png");
    boardTexture.setSmooth(true);
    boardSprite.setTexture(boardTexture);

    playerTexture.loadFromFile("./media/players.png");
    playerTexture.setSmooth(true);
    player1Sprite.setTexture(playerTexture);
    player2Sprite.setTexture(playerTexture);

    // Set player names
    font.loadFromFile("./media/fonts/Calibri.ttf");
    player1Name.setString(m_model->getFirstPlayerName());
    player2Name.setString(m_model->getSecondPlayerName());
    player1Name.setFillColor(sf::Color::Black);
    player2Name.setFillColor(sf::Color::Black);
    currentPlayerName.setFillColor(sf::Color::Red);
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

    m_Window.clear(sf::Color::White);

    // * Textures are 50x50 each
    for(int i = 0; i < mapSize; i++){
        for(int j = 0; j < mapSize; j++){
            switch (board.getTile(i,j)) {
            case empty:
                boardSprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
                break;

            case tile:
                boardSprite.setTextureRect(sf::IntRect(50, 0, tileSize, tileSize));
                break;
            
            case wall:
                boardSprite.setTextureRect(sf::IntRect(0, 50, tileSize, tileSize));
                break;
            }

            boardSprite.setPosition(i * tileSize + wallsHolderSize, j * tileSize);
            m_Window.draw(boardSprite);
        }   
    }

    player1Sprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
    player1Sprite.setPosition(x1 * tileSize + wallsHolderSize, y1 * tileSize);
    m_Window.draw(player1Sprite);

    player2Sprite.setTextureRect(sf::IntRect(30, 0, tileSize, tileSize));
    player2Sprite.setPosition(x2 * tileSize + wallsHolderSize, y2 * tileSize);
    m_Window.draw(player2Sprite);

    currentPlayerName.setString(m_model->getCurrentPlayerName());
    if (currentPlayerName.getString() == player1Name.getString()){
        currentPlayerName.setPosition(10,0);
        player2Name.setPosition(tileSize*mapSize + wallsHolderSize + 10, 0);
        m_Window.draw(currentPlayerName);
        m_Window.draw(player2Name);
    } else {
        player1Name.setPosition(10, 0);
        currentPlayerName.setPosition(tileSize*mapSize + wallsHolderSize + 10, 0);
        m_Window.draw(player1Name);
        m_Window.draw(currentPlayerName);
    }
    

    int wallsFirstPlayer, wallsSecondPlayer;
    wallsFirstPlayer = m_model->getFirstPlayerWalls();
    wallsSecondPlayer = m_model->getSecondPlayerWalls();

    boardSprite.setTextureRect(sf::IntRect(0, 50, tileSize, tileSize));

    for (int i = 0; i < wallsFirstPlayer; i++){
        boardSprite.setPosition(10, 45 + i*45);
        m_Window.draw(boardSprite);
        boardSprite.setPosition(10 + tileSize, 45 + i*45);
        m_Window.draw(boardSprite);
        boardSprite.setPosition(10 + tileSize*2, 45 + i*45);
        m_Window.draw(boardSprite);
    }

    for (int i = 0; i < wallsSecondPlayer; i++){
        boardSprite.setPosition(tileSize*mapSize + wallsHolderSize + 10, 45 + i*45);
        m_Window.draw(boardSprite);
        boardSprite.setPosition(tileSize*mapSize + wallsHolderSize + 10 + tileSize, 45 + i*45);
        m_Window.draw(boardSprite);
        boardSprite.setPosition(tileSize*mapSize + wallsHolderSize + 10 + tileSize*2, 45 + i*45);
        m_Window.draw(boardSprite);
    }
}

void View::drawPossibleMoves(){
    moves = m_model->getPossibleMoves();                    
    for (unsigned int i = 0; i < moves.size(); i++) {
        boardSprite.setTextureRect(sf::IntRect(100, 0, tileSize, tileSize));
        boardSprite.setPosition(moves[i].first * tileSize + wallsHolderSize, moves[i].second * tileSize);
        m_Window.draw(boardSprite);
    }
    m_Window.display();
}

sf::RenderWindow *View::getWindow(){
    return &m_Window;
}