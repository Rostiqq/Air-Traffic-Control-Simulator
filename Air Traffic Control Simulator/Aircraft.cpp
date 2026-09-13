#include "Aircraft.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <numbers>



void Aircraft::update(float deltaTime) {

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		heading -= turnSpeed * deltaTime;

		if (heading <= 0.f)
		{
			heading += 360.f;
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		heading += turnSpeed * deltaTime;

		if (heading >= 360.f)
		{
			heading -= 360.f;
		}
	}

	float radians = heading * std::numbers::pi_v<float> / 180.f;

	sf::Vector2f direction(std::sin(radians), -std::cos(radians));
	position += direction * speed * deltaTime;

	std::cout << "\rheading: " << heading << "    speed: " << speed << std::flush;
}

void Aircraft::draw(sf::RenderWindow& window) {
	shapeAircraft.setPosition(position);
	shapeAircraft.setFillColor(sf::Color::White);
	window.draw(shapeAircraft);
}
