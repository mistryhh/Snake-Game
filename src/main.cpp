#include <SFML/Graphics.hpp>

int main() {
    // SFML 3.0.0 syntax for creating a window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Snake Game");

    // Basic game loop
    while (window.isOpen()) {
        // Handle events (like clicking the 'X' to close)
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Clear the screen with a black color
        window.clear(sf::Color::Green);


        // Display what we have drawn
        window.display();
    }

    return 0;
}