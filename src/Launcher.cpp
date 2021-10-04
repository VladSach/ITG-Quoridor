#include "Launcher.h"

Launcher::Launcher() :
	singePlayerText("Single player", font, characterSize),
	multiplayerText("Multiplayer", font, characterSize),
	exitText("Exit", font, characterSize),
	againText("Do you want to exit?", font, characterSize),
	yesText("Yes", font, characterSize),
	noText("No", font, characterSize) {

	font.loadFromFile("./media/fonts/Calibri.ttf");
}

void Launcher::mainMenu(){

	sf::RenderWindow window(windowSize, launcherTitle);
	window.setPosition(centerWindow);
	
   	window.clear(backgroundColor);

	singePlayerText.setPosition(100, 160);
	multiplayerText.setPosition(100, 220);
	exitText.setPosition(100, 280);

    while (window.isOpen()) {
		singePlayerText.setFillColor(sf::Color::Black);
		multiplayerText.setFillColor(sf::Color::Black);
		exitText.setFillColor(sf::Color::Black);

		// * Highlight text on mouse hover and handle click
		if (sf::IntRect(100, 160, 229, 43).contains(sf::Mouse::getPosition(window))) {
			singePlayerText.setFillColor(sf::Color::Red); 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				window.close();
				singleplayer("Player", "Wally");
			}
		}
		if (sf::IntRect(100, 220, 207, 41).contains(sf::Mouse::getPosition(window))) {
			multiplayerText.setFillColor(sf::Color::Red); 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				window.close();
				multiplayer("Player1", "Player2");
			}
		}
		if (sf::IntRect(100, 280, 72, 37).contains(sf::Mouse::getPosition(window))) {
			exitText.setFillColor(sf::Color::Red); 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				return;
			}
		}

		// Ability to close window
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
				return;
            }
		}
 
		window.draw(singePlayerText);   
		window.draw(multiplayerText);
		window.draw(exitText);
		
		window.display();
	}

	return;
}

bool Launcher::exitMenu(){

	sf::RenderWindow window(windowSize, launcherTitle);
	window.setPosition(centerWindow);
   	window.clear(backgroundColor);

	againText.setPosition(185, 160);
	yesText.setPosition(195, 220);
	noText.setPosition(275, 220);

	againText.setFillColor(sf::Color::Black);
	
    while (window.isOpen()) {
		yesText.setFillColor(sf::Color::Black);
		noText.setFillColor(sf::Color::Black);
 
		if (sf::IntRect(195, 230, 55, 40).contains(sf::Mouse::getPosition(window))) {
			yesText.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				return false;
			}
		}
		if (sf::IntRect(275, 230, 50, 40).contains(sf::Mouse::getPosition(window))) {
			noText.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				return true;
			}
		}

		// Ability to close window
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
				return false;
            }
		}
 
		window.draw(againText);   
		window.draw(yesText);
		window.draw(noText);
		
		window.display();
	}

	return false;
}

void Launcher::singleplayer(const char* firstName, const char* secondName) {
    Player fp(mapSize/2, mapSize-1, firstName);
    Bot sp(mapSize/2, 0, secondName);

    Game game(fp, sp);
    View view(&game);
    Controller controller(&game, &view);
    controller.start();
}

void Launcher::multiplayer(const char* firstName, const char* secondName) {
    Player fp(mapSize/2, mapSize-1, firstName);
    Player sp(mapSize/2, 0, secondName);

    Game game(fp, sp);
    View view(&game);
    Controller controller(&game, &view);
    controller.start();
}