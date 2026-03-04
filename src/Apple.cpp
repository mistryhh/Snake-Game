#include "Apple.hpp"

Apple::Apple(int blockSize, int gridWidth, int gridHeight)
	: m_blockSize(blockSize), m_gridWidth(gridWidth), m_gridHeight(gridHeight)
{
	// Seed the random number generator with a random device
	std::random_device rd; 
	m_rng.seed(rd());

	// Spawn the apple
	spawn();
}

void Apple::spawn() {
	// Pick a random X between 0 and (gridWidth - 1)
	std::uniform_int_distribution<int> distX(0, m_gridWidth - 1);
	// Pick a random Y between 0 and (gridHeight - 1)
	std::uniform_int_distribution<int> distY(0, m_gridHeight - 1);

	m_position.x = distX(m_rng);
	m_position.y = distY(m_rng);
}
void Apple::render(sf::RenderWindow& window) {
	// Create a square shape for the apple
	sf::RectangleShape appleShape(sf::Vector2f(m_blockSize - 1.0f, m_blockSize - 1.0f));
	appleShape.setFillColor(sf::Color::Red);

	// Convert the grid coordinates back to pixel coordinates
	appleShape.setPosition(sf::Vector2f(m_position.x * m_blockSize, m_position.y * m_blockSize));

	window.draw(appleShape);
}
sf::Vector2i Apple::getPosition() const {
	return m_position;
}