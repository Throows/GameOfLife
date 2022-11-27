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

std::string stateToStr(CaseState state);

class GameOfLife
{
public:
	GameOfLife(uint length, uint width, std::shared_ptr<GOL::Logger> logger);
	~GameOfLife();

	void setup();
	void setupScreen();

	void Update(sf::RenderWindow &window, sf::Clock &clock);
	void resetGridTransition();
	void Render(sf::RenderWindow &window);

	void UpdateGrid(sf::Clock &clock);
	void UpdateEvents(sf::RenderWindow &window);

private:
	uint m_length;
	uint m_width;
	uint m_seed;
	std::vector<CaseState> m_grid;
	std::shared_ptr<GOL::Logger> logger;
	sf::RectangleShape square;
	bool needValidate = true;
	bool generationEnded = false;
	const int *cellRelativePos;
	std::array<int, 4> generationStats; // 0: DEAD, 1: ALIVE, 2: DA, 3: AD 
	int roundNumber = 0;
};

