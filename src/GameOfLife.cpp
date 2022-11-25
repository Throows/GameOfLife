#include "GameOfLife.h"
#include <stdlib.h>

GameOfLife::GameOfLife(uint caseNB, std::shared_ptr<Logger> logger) :
	m_caseNB(caseNB),
	m_seed(0),
	logger(std::move(logger))
{
}

GameOfLife::~GameOfLife()
{
}

void GameOfLife::setup()
{
	std::string seedS;
	std::getline(std::cin, seedS);
	this->m_seed = atoi(seedS.c_str());
	if (this->m_seed == 0)
		this->m_seed = rand();

	logger->logger.info("New Seed Found %d", this->m_seed);
}

void GameOfLife::setupScreen()
{
	this->square = sf::CircleShape(15.f, 4);
	this->square.setRotation(45);
	this->grid.clear();

	for (int i = 1; i <= this->m_caseNB; i++)
	{
		CaseState gridCase = (this->m_seed / i) % 2 ? CaseState::ALIVE : CaseState::DEAD;
		this->grid.push_back(gridCase);
	}

}

void GameOfLife::Update(sf::RenderWindow &window, sf::Clock &clock)
{
	UpdateEvents(window);
	sf::Time ticks = clock.getElapsedTime();
	if(ticks.asMilliseconds() >= 500)
		UpdateGrid(clock);
	else if (!needValidate)
	{
		validateUpdate();
		needValidate = false;
	}

}

void GameOfLife::validateUpdate()
{
	for(auto caseGrid : this->m_grid)
	{
		switch (caseGrid)
		{
		case CaseState::D_TO_A:
			caseGrid = CaseState::ALIVE;
			break;
		case CaseState::A_TO_D:
			caseGrid = CaseState::DEAD;
			break;
		}
	}
}

void GameOfLife::Render(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);

	for (int x = 1; x <= 60; x++)
	{
		for (int y = 1; y <= 60; y++)
		{
			switch (this->m_grid.at(x*y))
			{
			case CaseState::ALIVE:
			case CaseState::D_TO_A:
				this->square.setFillColor(sf::Color::White);
				break;
			case CaseState::DEAD:
			case CaseState::A_TO_D:
			default:
				this->square.setFillColor(sf::Color::Black);
				break;
			}
			this->square.setPosition(sf::Vector2f(x*15, y*15));
			window.draw(this->square);
		}
	}
	window.display();
}

void GameOfLife::UpdateGrid(sf::Clock &clock)
{
	for (int y = 1; y <= 60; y++)
	{
		for (int x = 0; x < 60; x++)
		{
			if (this->m_grid.at(x * y) == CaseState)
			{
				
			}
		}
	}

	clock.restart();
	needValidate = true;
}

void GameOfLife::UpdateEvents(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}


