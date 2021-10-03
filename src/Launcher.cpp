#include "Launcher.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


Launcher::Launcher(bool *playAgain)
	:singePlayer("Single player", font, 40),
	multiplayer("Multiplayer", font, 40),
	exit("Exit", font, 40),
	again("Play again?", font, 40),
	yes("Yes", font, 40),
	no("No", font, 40)
{
	

	bool a = playAgain;
	char answer;

	font.loadFromFile("./media/fonts/Calibri.ttf");

}

char Launcher::menu(){
	isMenu = 1;

	sf::RenderWindow window(sf::VideoMode({510, 510}), "Quoridor");
   	window.clear(sf::Color(0x80, 0x80, 0x0));

	singePlayer.setPosition(100, 160);
	multiplayer.setPosition(100, 220);
	exit.setPosition(100, 280);

    while (isMenu)
	{
		singePlayer.setColor(sf::Color::Black);
		multiplayer.setColor(sf::Color::Black);
		exit.setColor(sf::Color::Black);
		menuNum = 0;
 
		if (sf::IntRect(100, 160, 229, 43).contains(sf::Mouse::getPosition(window))) { singePlayer.setColor(sf::Color::Red); menuNum = 1; }
		if (sf::IntRect(100, 220, 207, 41).contains(sf::Mouse::getPosition(window))) { multiplayer.setColor(sf::Color::Red); menuNum = 2; }
		if (sf::IntRect(100, 280, 72, 37).contains(sf::Mouse::getPosition(window))) { exit.setColor(sf::Color::Red); menuNum = 3; }
 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) { isMenu = false; answer = 's'; return answer; }
			if (menuNum == 2) { isMenu = false; answer = 'm'; return answer; }
			if (menuNum == 3)  { window.close(); isMenu = false; answer = 'e'; return answer; }
 
		}
 
		window.draw(singePlayer);   
		window.draw(multiplayer);
		window.draw(exit);
		
		window.display();
	}
}

char Launcher::oneMore(){
	bool isOneMore = 1;

	sf::RenderWindow window(sf::VideoMode({510, 510}), "Quoridor");
   	window.clear(sf::Color(0x80, 0x80, 0x0));

	again.setPosition(185, 160);
	yes.setPosition(195, 220);
	no.setPosition(275, 220);

	again.setColor(sf::Color::Black);
	
    while (isOneMore)
	{
		yes.setColor(sf::Color::Black);
		no.setColor(sf::Color::Black);
		menuNum = 0;
 
		if (sf::IntRect(195, 230, 55, 40).contains(sf::Mouse::getPosition(window))) { yes.setColor(sf::Color::Red); menuNum = 1; }
		if (sf::IntRect(275, 230, 50, 40).contains(sf::Mouse::getPosition(window))) { no.setColor(sf::Color::Red); menuNum = 2; }
 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) { isOneMore = false; answer = 'y'; return answer; }
			if (menuNum == 2) { isOneMore = false; answer = 'n'; return answer; }
 
		}
 
		window.draw(again);   
		window.draw(yes);
		window.draw(no);
		
		window.display();
	}
}