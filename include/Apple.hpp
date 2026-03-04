#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Apple {
public:
	// the block size and the grid dimensions to know where we can spawn the apple
	Apple(int blockSize, int gridWidth, int gridHeight);

	void spawn();
	void render(sf::RenderWindow& window);

	sf::Vector2i getPosition() const;
private:
	int m_blockSize;
	int m_gridWidth;
	int m_gridHeight;
	sf::Vector2i m_position;

	std::mt19937 m_rng; // Random number generator
};