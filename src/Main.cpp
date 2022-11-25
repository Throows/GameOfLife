#include "GameOfLife.h"
#include <SFML/Main.hpp>
#include "Logger.h"
#include <memory>

int main() 
{
	std::shared_ptr<GOL::Logger> logger = std::make_shared<GOL::Logger>();
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Game Of Life", sf::Style::Default);
	logger->setup("log.txt", "GameOfLife");
	GameOfLife gameOfLife(3600, logger);
	sf::Clock clock;

	gameOfLife.setup();
	gameOfLife.setupScreen();

	while (window.isOpen())
	{
		gameOfLife.Update(window, clock);
		gameOfLife.Render(window);
	}

	return 0;

}