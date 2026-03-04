#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class Direction {
	Up,
	Down,
	Left,
	Right,
	None
};

class Snake {
public:
	// Pass in the size of the grid blocks
	Snake(int blockSize);

	void setDirection(Direction newDirection);
	void move();
	void render(sf::RenderWindow& window);
private:
	int m_blockSize;
	Direction m_direction;

	// The vector holding the grid cooridinates of the snake's body
	// m_body.front() is the head, m_body.back() is the tail
	std::vector<sf::Vector2i> m_body;
};