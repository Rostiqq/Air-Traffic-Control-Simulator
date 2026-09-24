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
	destinationText.setCharacterSize(10);

	this->callsign = newCallsign;
	label.setString(newCallsign);
	this->position = position;
}

void Aircraft::update(float deltaTime,sf::Vector2f airportPosition) {

	sf::Vector2f directionToTarget = getDirectionTo(airportPosition);

	float angle = std::atan2(directionToTarget.x, -directionToTarget.y);
	float targetHeading = angle * 180.f / std::numbers::pi_v<float>;

	if (targetHeading < 0.f)
		targetHeading += 360.f;

	float currentHeading = getHeading();
	float difference = targetHeading - currentHeading;

	if (difference > 180.f)
		difference -= 360.f;

	if (difference < -180.f)
		difference += 360.f;

	if (difference > 0)
		heading += turnSpeed * deltaTime;
	else if (difference < 0)
	{
		heading -= turnSpeed * deltaTime;
	}
	
	if (heading >= 360.f)
	{
		heading -= 360.f;
	}
	else if (heading < 0.f)
	{
		heading += 360.f;
	}


	float radians = heading * std::numbers::pi_v<float> / 180.f;

	sf::Vector2f direction(std::sin(radians), -std::cos(radians));
	position += direction * speed * deltaTime;

	speedText.setString("SPD: " + std::to_string(static_cast<int>(speed)));
	headingText.setString("HDG: " + std::to_string(static_cast<int>(heading)));
}

void Aircraft::draw(sf::RenderWindow& window) {
	shapeAircraft.setPosition(position);
	label.setPosition(position + textOffset);
	speedText.setPosition(position + speedOffset);
	headingText.setPosition(position + headingOffset);
	destinationText.setPosition(position + destinationOffset);

	shapeAircraft.setFillColor(sf::Color::White);

	window.draw(shapeAircraft);
	window.draw(label);
	window.draw(speedText);
	window.draw(headingText);
	window.draw(destinationText);
}

void Aircraft::setDestination(const std::string& newDestination) {
	destination = newDestination;
	destinationText.setString("DEST: " + destination);
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


sf::Vector2f Aircraft::getDirectionTo(sf::Vector2f targetPosition) {
	sf::Vector2f direction = targetPosition - position;
	return direction;
}
