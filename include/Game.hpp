#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Snake.hpp"
#include "Apple.hpp"

enum class GameState {
	MainMenu,
	Playing,
	GameOver
};

class Game {
public:
	// Constructor
	Game();

	// The main public function to run the game loop
	void run();

private:
	// Helper methods for the game loop
	void processEvents();
	void update();
	void render();

	void initText();

	// Member variables
	sf::RenderWindow m_window;

	Snake m_snake;
	Apple m_apple;

	// Timing variables to control snake speed
	sf::Clock m_clock;
	float m_timer;
	float m_delay;

	// Variables to track the game state and score
	GameState m_state;
	int m_score;
	sf::Font m_font;
	sf::Text m_scoreText;
	sf::Text m_menuText;
};