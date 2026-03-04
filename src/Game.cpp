#include "Game.hpp"

// Constructor: Initialize the game window
Game::Game() 
	: m_window(sf::VideoMode({ 800, 600 }), "Snake Game")
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
	}
}

// Update game logic 
void Game::update() {

}

void Game::render() {
	// Clear the old frame
	m_window.clear(sf::Color::Black);

	// Draw the new frame

	// Display it in the window
	m_window.display();
}
