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
		newHead.y += 1; 
	}
	if (m_direction == Direction::Left) {
		newHead.x -= 1; 
	}
	if (m_direction == Direction::Right) {
		newHead.x += 1; 
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

bool Snake::checkCollision(int gridWidth, int gridHeight) {
	
	sf::Vector2i head = m_body.front();

	// Check for wall collision
	if (head.x < 0 || head.x >= gridWidth || head.y < 0 || head.y >= gridHeight) {
		return true;
	}
	// Check for self collision
	for (size_t i = 1; i < m_body.size(); i++) {
		if(head.x == m_body[i].x && head.y == m_body[i].y) {
			return true;
		}
	}
	// No collision detected
	return false;
}
void Snake::reset() {
	// Empty the current body
	m_body.clear();
	// Rebuild the Snake
	m_body.push_back({ 20, 15 }); // Head
	m_body.push_back({ 20, 16 }); // Body
	m_body.push_back({ 20, 17 }); // Tail

	// Stop moving 
	m_direction = Direction::None;
}

// Return the coordinate of the head
sf::Vector2i Snake::getHead() const {
	return m_body.front();
}

// Grow the snake by duplicating the tail segment
void Snake::grow() {
	m_body.push_back(m_body.back());
}