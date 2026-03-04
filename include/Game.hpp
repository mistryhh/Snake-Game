#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Apple.hpp"

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

	// Member variables
	sf::RenderWindow m_window;

	
	Snake m_snake;
	Apple m_apple;

	// Timing variables to control snake speed
	sf::Clock m_clock;
	float m_timer;
	float m_delay;
};