#include "Game.hpp"
#include <iostream>

// Constructor: Initialize the game window
Game::Game()
	: m_window(sf::VideoMode({ 800, 600 }), "Snake Game"),
	m_snake(20),
	m_apple(20, 40, 30),
	m_timer(0.0f),
	m_delay(0.1f),
	m_state(GameState::MainMenu), 
	m_score(0),
	m_highScore(0),
	m_scoreText(m_font),         
	m_menuText(m_font)
{
	loadHighScore();
	initText();
}

void Game::loadHighScore() {
	std::ifstream file("assets/highscore.txt");
	if (file.is_open()) {
		file >> m_highScore;
		file.close();
	}
}
void Game::saveHighScore() {
	std::ofstream file("assets/highscore.txt");
	if (file.is_open()) {
		file << m_highScore;
		file.close();
	}
}

void Game::initText() {
	if (!m_font.openFromFile("assets/Cornerstone_Regular.ttf")) {
		std::cerr << "Failed to load font! Make sure 'assets/Cornerstone_Regular.ttf' exists.\n";
	}

	// Setup score text
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(24);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(sf::Vector2f(10.0f, 10.0f));
	m_scoreText.setString("Score: 0");

	// Setup Menu Text
	m_menuText.setFont(m_font);
	m_menuText.setCharacterSize(36);
	m_menuText.setFillColor(sf::Color::Green);
	m_menuText.setPosition(sf::Vector2f(180.0f, 250.0f));
	m_menuText.setString("SNAKE GAME\nHigh Score: " + std::to_string(m_highScore) + "\nPress ENTER to Start");
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
			if (m_state == GameState::MainMenu || m_state == GameState::GameOver) {
				if (keyPressed->code == sf::Keyboard::Key::Enter) {
					m_snake.reset();
					m_apple.spawn();
					m_score = 0;
					m_scoreText.setString("Score: 0");
					m_state = GameState::Playing; // Switch to gameplay!
				}
			}
			else if (m_state == GameState::Playing) {
				if (keyPressed->code == sf::Keyboard::Key::Up) m_snake.setDirection(Direction::Up);
				else if (keyPressed->code == sf::Keyboard::Key::Down) {
					m_snake.setDirection(Direction::Down);
				}
				else if (keyPressed->code == sf::Keyboard::Key::Left) {
					m_snake.setDirection(Direction::Left);
				}
				else if (keyPressed->code == sf::Keyboard::Key::Right) {
					m_snake.setDirection(Direction::Right);
				}
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

		if (m_snake.getHead() == m_apple.getPosition()) {
			m_snake.grow();
			m_apple.spawn();

			m_score += 10;
			m_scoreText.setString("Score: " + std::to_string(m_score));

			// Update High Score in real-time if we beat it
			if (m_score > m_highScore) {
				m_highScore = m_score;
			}
		}
		if (m_snake.checkCollision(40, 30)) {
			saveHighScore(); // Save to the file when we die!

			m_state = GameState::GameOver;
			// NEW: Show both scores on the Game Over screen
			m_menuText.setString("GAME OVER!\nScore: " + std::to_string(m_score) +
				"\nHigh Score: " + std::to_string(m_highScore) +
				"\nPress ENTER to Restart");
		}

		// Check for collisions right after moving the snake
		if (m_snake.checkCollision(40, 30)) {
			m_state = GameState::GameOver; // Trigger Game Over state
			m_menuText.setString("GAME OVER!\nFinal Score: " + std::to_string(m_score) + "\nPress ENTER to Restart");
		}

	}	
}

void Game::render() {
	// Clear the old frame
	m_window.clear(sf::Color::Black);

	if (m_state == GameState::Playing) {
		m_apple.render(m_window);
		m_snake.render(m_window);
		m_window.draw(m_scoreText);
	}
	// Otherwise, draw the menu UI
	else {
		m_window.draw(m_menuText);
	}

	m_window.display();
}
