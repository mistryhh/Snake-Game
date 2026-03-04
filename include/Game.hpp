#pragma once
#include <SFML/Graphics.hpp>

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
};