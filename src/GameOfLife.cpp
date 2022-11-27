#include "GameOfLife.h"
#include <stdlib.h>
#include <iostream>
#include <random>
#include <cstdint>


GameOfLife::GameOfLife(uint length, uint width, std::shared_ptr<GOL::Logger> logger) :
	m_length(length),
	m_width(width),
	m_seed(0),
	logger(std::move(logger)) 
{
	int len = static_cast<int>(m_length);
	this->cellRelativePos = new int[8]
	{ 
		-1, 
		-len - 1, -len, -len + 1, 
		 1, 
		 len - 1,  len,  len + 1
	};
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
	spdlog::info("New Seed Found {}", this->m_seed);
	srand(this->m_seed);
}

void GameOfLife::setupScreen()
{
	this->square = sf::RectangleShape(sf::Vector2f(15.f, 15.f));
	int aliveCells = 0, deadCells = 0;

	for (int i = 1; i <= (m_length * m_width); i++)
	{
		bool cell = (std::rand() % 100) >= 90;
		CaseState cellState;
		if(cell)
		{
			cellState = CaseState::ALIVE;
			aliveCells++;
		}
		else
		{
			cellState = CaseState::DEAD;
			deadCells++;
		}
		this->m_grid.push_back(cellState);
	}
	spdlog::trace("================ Grid L: {}, W: {} ================", this->m_length, this->m_width);
	for (int i = 0; i < (m_length * m_width); i+=m_width)
	{
		std::string buffer = "{";
		for (int x = 0; x < m_length; x++)
		{
			buffer += stateToStr(this->m_grid.at(i + x));
			if(m_length-1 != x)
				buffer += ",";
		}
		buffer += "}";
		spdlog::trace("{}", buffer.c_str());
	}
	spdlog::trace("================================================");
	spdlog::info("Seed Stats : {} Cells begin alive, {} dead", aliveCells, deadCells);
}

void GameOfLife::Update(sf::RenderWindow &window, sf::Clock &clock)
{
	UpdateEvents(window);
	sf::Time ticks = clock.getElapsedTime();
	bool ended = this->generationEnded;
	if(ticks.asMilliseconds() >= 100 && !this->generationEnded)
	{
		resetGridTransition();
		UpdateGrid(clock);
	}

	if(ended != this->generationEnded)
	{
		spdlog::info("Stable State reached after {} rounds ", roundNumber);
		spdlog::info("Generation Stats : {} cells remain alive, {} are dead", 
								this->generationStats[1],
								this->generationStats[0]);
		spdlog::info("Geneation Stats : {} cells stay between life and death",
							 	this->generationStats[2]);
	}
}

void GameOfLife::resetGridTransition()
{
	std::array<int, 4> cellsStats = {0, 0, 0, 0};
	for(auto& cell : this->m_grid)
	{
		if (cell == CaseState::D_TO_A)
		{
			++cellsStats[2];
			cell = CaseState::ALIVE;
		}
		else if (cell == CaseState::A_TO_D)
		{
			++cellsStats[3];
			cell = CaseState::DEAD;
		}
		else if (cell == CaseState::ALIVE)
			++cellsStats[1];
		else if (cell == CaseState::DEAD)
			++cellsStats[0];
	}
	spdlog::trace("Cells Stats : {} Dead Cells; {} Alive Cells; {} Reviving; {} Dying",
						  this->generationStats[0],
						  this->generationStats[1],
						  this->generationStats[2],
						  this->generationStats[3]);

	if (cellsStats == this->generationStats)
		this->generationEnded = true;

	this->generationStats = cellsStats;
}

void GameOfLife::Render(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);

	int ind = 0;
	for (auto &cell : this->m_grid)
	{
		if (cell == CaseState::ALIVE)
			this->square.setFillColor(sf::Color::White);
		else if (cell == CaseState::D_TO_A)
			this->square.setFillColor(sf::Color::Green);
		else if (cell == CaseState::DEAD) 
			this->square.setFillColor(sf::Color::Black);
		else if (cell == CaseState::A_TO_D)
			this->square.setFillColor(sf::Color::Red);

		this->square.setPosition(sf::Vector2f(((ind % m_length) + 1) * 15, (ind / m_width) * 15));
		window.draw(this->square);
		ind++;
	}
	window.display();
}

void GameOfLife::UpdateGrid(sf::Clock &clock)
{
	for(int pos = 0; pos < this->m_grid.size(); pos++)
	{
		uint8_t aliveCells = 0;
		for(uint8_t i = 0; i < 8; i++)
		{
			int cellPos = pos + this->cellRelativePos[i];
			if (cellPos < (m_length * m_width) && cellPos >= 0)
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
	roundNumber++;
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

std::string stateToStr(CaseState state)
{
	std::string stateStr = "0";
	if(state == CaseState::ALIVE || state == CaseState::D_TO_A)
		stateStr = "1";
	return stateStr;
}
