#include <iostream>
#include <vector>
#include <numbers>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Aircraft.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "ATC Simulator", sf::Style::Titlebar);
	sf::Clock clock;

	Aircraft aircraft;



	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		
		window.clear(sf::Color(10, 15, 25));

		aircraft.update(deltaTime);
		aircraft.draw(window);

		
		window.display();
	}

	return 0;
}