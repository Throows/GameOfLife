#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 
#include <algorithm>
#include <iterator>
#include <iostream>

class GameOfLife
{
public:
	GameOfLife();
	~GameOfLife();

	void Update(sf::RenderWindow &window, sf::Clock &clock);
	void Render(sf::RenderWindow &window);

	void UpdateGrid(sf::Clock &clock);
	void UpdateEvents(sf::RenderWindow &window);

private:
	//grid : 900*900 px    1 square : 15*15 px
	int m_grid[60][60] = {};
	sf::CircleShape square;

	void createPattern(int xCord, int yCoord);

};

