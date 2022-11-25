#include "GameOfLife.h"
#include <stdlib.h>
#include <iostream>
#include <random>
#include <cstdint>


GameOfLife::GameOfLife(uint caseNB, std::shared_ptr<GOL::Logger> logger) :
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
	std::random_device dev;
	std::mt19937 generator(dev());
	std::uniform_int_distribution<uint64_t> distr(0, UINT64_MAX);
	this->m_seed = distr(generator);
	logger->logger->info("New Seed Found {}", this->m_seed);
}

void GameOfLife::setupScreen()
{
	this->square = sf::CircleShape(15.f, 4);
	this->square.setRotation(45);

	for (int i = 1; i <= this->m_caseNB; i++)
	{
		CaseState gridCase = (this->m_seed / i) % 2 ? CaseState::ALIVE : CaseState::DEAD;
		this->m_grid.push_back(gridCase);
	}
}

void GameOfLife::Update(sf::RenderWindow &window, sf::Clock &clock)
{
	UpdateEvents(window);
	sf::Time ticks = clock.getElapsedTime();
	if(ticks.asMilliseconds() >= 100)
		UpdateGrid(clock);
	if (needValidate)
	{
		validateUpdate();
		needValidate = false;
	}

}

void GameOfLife::validateUpdate()
{
	for(auto& cell : this->m_grid)
	{
		if (cell == CaseState::D_TO_A)
			cell = CaseState::ALIVE;
		else if (cell == CaseState::A_TO_D)
			cell = CaseState::DEAD;
	}
}

void GameOfLife::Render(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);

	int ind = 0;
	for (auto &cell : this->m_grid)
	{
		if (cell == CaseState::D_TO_A || cell == CaseState::ALIVE)
			this->square.setFillColor(sf::Color::White);
		else if (cell == CaseState::D_TO_A || cell == CaseState::DEAD)
			this->square.setFillColor(sf::Color::Black);

		this->square.setPosition(sf::Vector2f(((ind % 60)+1) * 15, (ind/60) * 15));
		window.draw(this->square);
		ind++;
	}
	window.display();
}

const int8_t cellRelativePos[] = { -1, -60-1, -60, -60+1, 1, 60+1, 60, 60-1 };

void GameOfLife::UpdateGrid(sf::Clock &clock)
{
	for(int pos = 0; pos < this->m_grid.size(); pos++)
	{
		uint8_t aliveCells = 0;
		for(uint8_t i = 0; i < 8; i++)
		{
			int cellPos = pos + cellRelativePos[i];
			if (cellPos < m_caseNB && cellPos >= 0)
			{
				if (this->m_grid.at(cellPos) == CaseState::ALIVE || this->m_grid.at(cellPos) == CaseState::A_TO_D)
					aliveCells++;
			}
		}

		if(this->m_grid.at(pos) == CaseState::ALIVE)
		{
			if (aliveCells < 2 || aliveCells > 3)  // Under/Over Population
				this->m_grid.at(pos) = CaseState::A_TO_D;
		}
		else if (this->m_grid.at(pos) == CaseState::DEAD)
		{
			if (aliveCells == 3)
				this->m_grid.at(pos) = CaseState::D_TO_A;
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


