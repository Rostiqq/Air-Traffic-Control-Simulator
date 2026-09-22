#include "Aircraft.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <numbers>

Aircraft::Aircraft(const std::string& newCallsign,sf::Vector2f position) : label(font) {
	if (!font.openFromFile("GeistMono-Regular.ttf"))
	{
		std::cout << "Font sa nepodarilo nacitat!\n";
	}

	
	label.setCharacterSize(15);
	speedText.setCharacterSize(12);
	headingText.setCharacterSize(12);

	this->callsign = newCallsign;
	label.setString(newCallsign);
	
	this->position = position;
}

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		speed += acceleration * deltaTime;

		if (speed >= maxSpeed)
		{
			speed = maxSpeed;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		speed -= acceleration * deltaTime;

		if (speed <= 0.f)
		{
			speed = 0.f;
		}
	}

	float radians = heading * std::numbers::pi_v<float> / 180.f;

	sf::Vector2f direction(std::sin(radians), -std::cos(radians));
	position += direction * speed * deltaTime;

	speedText.setString("SPD: " + std::to_string(static_cast<int>(speed)));
	headingText.setString("HDG: " + std::to_string(static_cast<int>(heading)));

	std::cout << "\rheading: " << heading << "    speed: " << speed << std::flush;
}

void Aircraft::draw(sf::RenderWindow& window) {
	shapeAircraft.setPosition(position);
	label.setPosition(position + textOffset);
	speedText.setPosition(position + speedOffset);
	headingText.setPosition(position + headingOffset);

	shapeAircraft.setFillColor(sf::Color::White);

	window.draw(shapeAircraft);
	window.draw(label);
	window.draw(speedText);
	window.draw(headingText);
}

float Aircraft::getSpeed()
{
	return speed;
}

float Aircraft::getHeading()
{
	return heading;
}

bool Aircraft::isClicked(sf::Vector2i mousePosition) {
	float dx = mousePosition.x - position.x;
	float dy = mousePosition.y - position.y;
	float different = sqrt(dx * dx + dy * dy);
	
	return different <= 10.f;
}