#pragma once

#include "GameOfLife.h"
#include <SFML/Main.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(900, 900), "Game Of Life", sf::Style::Default);
	GameOfLife gameOfLife;
	sf::Clock clock;

	while (window.isOpen())
	{
		gameOfLife.Update(window, clock);
		gameOfLife.Render(window);
	}

	return 0;

}