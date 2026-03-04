#include "Game.hpp"

// Constructor: Initialize the game window
Game::Game()
	: m_window(sf::VideoMode({ 800, 600 }), "SFML Snake Game"),
	m_snake(20),
	m_timer(0.0f),
	m_delay(0.1f)
{
}

// The core Game loop
void Game::run() {
	while(m_window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

// Handle user input
void Game::processEvents() {
	while (const std::optional<sf::Event> event = m_window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			m_window.close();
		}

		// SMFL 3.0.0 specific way to check key presses safely
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->code == sf::Keyboard::Key::Up) {
				m_snake.setDirection(Direction::Up);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Down) {
				m_snake.setDirection(Direction::Down);
			}
			else if (keyPressed->code == sf::Keyboard::Key::Left) {
				m_snake.setDirection(Direction::Left);
			}
			else if(keyPressed->code == sf::Keyboard::Key::Right) {
				m_snake.setDirection(Direction::Right);
			}
		}
	}
}

// Update game logic 
void Game::update() {
	// Get the time passed since the last frame and add it to the timer
	float time = m_clock.restart().asSeconds();
	m_timer += time;

	// Only move the snake if enough time has acumulated
	if(m_timer > m_delay) {
		m_timer = 0.0f; // Reset the time
		m_snake.move(); // Move the snake one block
	}
}

void Game::render() {
	// Clear the old frame
	m_window.clear(sf::Color::Black);

	// Draw the new frame
	m_snake.render(m_window);

	// Display it in the window
	m_window.display();
}
