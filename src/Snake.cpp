#include "Snake.hpp"

// Intialise the snake in the middle of the grid
Snake::Snake(int blockSize) : m_blockSize(blockSize), m_direction(Direction::None) {
	m_body.push_back({ 20, 15 }); // Head
	m_body.push_back({ 20, 16 }); // Body
	m_body.push_back({ 20, 17 }); // Tail
}
void Snake::setDirection(Direction newDirection) {
	// Prevent the snake from reversing on itself
	if (m_direction == Direction::Up && newDirection == Direction::Down) {
		return;
	}
	if (m_direction == Direction::Down && newDirection == Direction::Up) {
		return;
	}
	if (m_direction == Direction::Left && newDirection == Direction::Right) {
		return;
	}
	if (m_direction == Direction::Right && newDirection == Direction::Left) {
		return;
	}

	m_direction = newDirection;
}

void Snake::move() {
	// Dont move if the game just started and no key is pressed
	if (m_direction == Direction::None) {
		return;
	}

	// Get the current head position
	sf::Vector2i newHead = m_body.front();

	// Calculate the new head position based on direction
	if (m_direction == Direction::Up) {
		newHead.y -= 1;
	}
	if (m_direction == Direction::Down) {
		newHead.y -= 1;
	}
	if (m_direction == Direction::Left) {
		newHead.y -= 1;
	}
	if (m_direction == Direction::Right) {
		newHead.y -= 1;
	}

	// Add the new head to the front of the vector
	m_body.insert(m_body.begin(), newHead);

	// Remove the tail
	m_body.pop_back();
}

void Snake::render(sf::RenderWindow& window) {
	// Create a square shape for a single snake segment
	sf::RectangleShape segement(sf::Vector2f(m_blockSize - 1.0f, m_blockSize - 1.0f));
	segement.setFillColor(sf::Color::Green);

	// Loop through every coordinate in the body
	for (const auto& part : m_body) {
		// Convert the grid coordinates back to pixel coordinates
		segement.setPosition(sf::Vector2f(part.x * m_blockSize, part.y * m_blockSize));
		window.draw(segement);
	}
}