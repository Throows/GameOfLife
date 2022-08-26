#include "GameOfLife.h"

GameOfLife::GameOfLife()
{
	this->square = sf::CircleShape(15.f, 4);
	this->square.setRotation(45);

	this->m_grid[10][10] = 1;
	this->m_grid[10][11] = 1;
	this->m_grid[10][12] = 1;

	this->m_grid[30][30] = 1;
	this->m_grid[32][30] = 1;
	this->m_grid[31][29] = 1;
	this->m_grid[31][31] = 1;
	

	this->createPattern(23, 43);
	this->createPattern(24, 46);
	this->createPattern(10, 30);
	this->createPattern(12, 33);
	

}

GameOfLife::~GameOfLife()
{
}

void GameOfLife::Update(sf::RenderWindow &window, sf::Clock &clock)
{
	UpdateEvents(window);
	sf::Time ticks = clock.getElapsedTime();
	if(ticks.asMilliseconds() >= 500)
		UpdateGrid(clock);

}

void GameOfLife::Render(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);

	for (int x = 0; x < 60; x++)
	{
		for (int y = 0; y < 60; y++)
		{
			switch (this->m_grid[x][y])
			{
			case 1:
				this->square.setFillColor(sf::Color::White);
				break;
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

	int newGrid[60][60];
	memcpy(newGrid, this->m_grid, 60*60*sizeof(int));

	for (int x = 0; x < 60; x++)
	{
		for (int y = 0; y < 60; y++)
		{
			int aliveGridSum = 0;
			if (( x > 1 && x < 59 ) && (y > 1 && y < 59)) {
				
				aliveGridSum += this->m_grid[x][y - 1];
				aliveGridSum += this->m_grid[x][y + 1];

				aliveGridSum += this->m_grid[x - 1][y - 1];
				aliveGridSum += this->m_grid[x - 1][y + 1];
				aliveGridSum += this->m_grid[x - 1][y];

				aliveGridSum += this->m_grid[x + 1][y - 1];
				aliveGridSum += this->m_grid[x + 1][y + 1];
				aliveGridSum += this->m_grid[x + 1][y];
				
			}

			if(this->m_grid[x][y] == 0 && aliveGridSum == 3){
				newGrid[x][y] = 1;
			}
			if (this->m_grid[x][y] == 1) {
				if(aliveGridSum != 3 && aliveGridSum != 2) newGrid[x][y] = 0;
			}
		}
	}

	//std::cout << "Grid updated ! " << std::endl;

	memcpy(this->m_grid, newGrid, 60 * 60 * sizeof(int));

	clock.restart();

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

void GameOfLife::createPattern(int xCord, int yCoord)
{
	this->m_grid[xCord][yCoord] = 1;
	this->m_grid[xCord+1][yCoord+1] = 1;
	this->m_grid[xCord+1][yCoord+2] = 1;
	this->m_grid[xCord][yCoord+2] = 1;
	this->m_grid[xCord-1][yCoord+2] = 1;
}


