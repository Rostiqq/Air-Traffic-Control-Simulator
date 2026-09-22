#include <iostream>
#include <vector>
#include <numbers>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Aircraft.hpp"
#include "Airport.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "ATC Simulator", sf::Style::Titlebar);
	sf::Clock clock;
	sf::Vector2i mousePosition;

	std::vector<Aircraft> aircrafts;
	aircrafts.reserve(3);
	aircrafts.emplace_back("MA345", sf::Vector2f{ 300.f,400.f });
	aircrafts.emplace_back("NO123", sf::Vector2f{ 800.f,200.f });
	aircrafts.emplace_back("BA875", sf::Vector2f{ 1000.f,600.f });
	int selectedAircraft = 0;

	Airport airport;

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
				
				if (mouse->button == sf::Mouse::Button::Left)
				{
					mousePosition = mouse->position;
				}
			}
		}
		
		window.clear(sf::Color(10, 15, 25));

		for (int i = 0; i < aircrafts.size(); i++)
		{
			if (aircrafts[i].isClicked(mousePosition))
			{
				selectedAircraft = i;
			}
		}

		for (int i = 0; i < aircrafts.size(); i++)
		{
			if (i == selectedAircraft)
			{
				aircrafts[i].update(deltaTime);
			}

			aircrafts[i].draw(window);
		}
		airport.drawAirport(window);

		window.display();
	}

	return 0;
}