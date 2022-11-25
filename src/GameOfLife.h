#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 
#include <vector>
#include "Logger.h"

enum CaseState : uint8_t
{
	DEAD = 0,
	ALIVE = 1,
	D_TO_A = 2,
	A_TO_D = 3
};

class GameOfLife
{
public:
	GameOfLife(uint caseNB, std::shared_ptr<Logger> logger);
	~GameOfLife();

	void setup();
	void setupScreen();

	void Update(sf::RenderWindow &window, sf::Clock &clock);
	void validateUpdate();
	void Render(sf::RenderWindow &window);

	void UpdateGrid(sf::Clock &clock);
	void UpdateEvents(sf::RenderWindow &window);

private:
	uint m_caseNB;
	uint m_seed;
	std::vector<CaseState> grid;
	sf::CircleShape square;
	std::shared_ptr<Logger> logger;
	bool needValidate = true;
};

