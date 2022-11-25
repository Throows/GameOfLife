#include "GameOfLife.h"
#include <SFML/Main.hpp>
#include "Logger.h"

int main() {

	auto logger = std::make_shared<Logger>();
	logger->setup("log.txt", "GameOfLife");
	spdlog::set_pattern("[%T] [%n] [%^---%L---%$] %v");
	sf::RenderWindow window(sf::VideoMode(900, 900), "Game Of Life", sf::Style::Default);
	GameOfLife gameOfLife(3600, logger);
	sf::Clock clock;

	gameOfLife.setup();

	while (window.isOpen())
	{
		gameOfLife.Update(window, clock);
		gameOfLife.Render(window);
	}

	return 0;

}