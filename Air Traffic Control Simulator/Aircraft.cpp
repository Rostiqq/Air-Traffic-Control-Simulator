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
	stateText.setCharacterSize(10);

	this->callsign = newCallsign;
	label.setString(newCallsign);
	this->position = position;
}

void Aircraft::update(float deltaTime,float runwayHeading, sf::Vector2f runwayCenter) 
{
	float targetHeading = 0.f;
	if (state == AircraftState::Landed)
	{
		return;
	}
	
	if (state == AircraftState::Flying && isNear(runwayCenter))
	{
		state = AircraftState::Landing;
		landingStartSpeed = speed;
		landingStartDistance = getDistanceTo(runwayCenter);
	}


	sf::Vector2f directionToTarget = getDirectionTo(runwayCenter);

	float angle = std::atan2(directionToTarget.x, -directionToTarget.y);
	targetHeading = angle * 180.f / std::numbers::pi_v<float>;

	if (targetHeading < 0.f)
		targetHeading += 360.f;
	if (state == AircraftState::Flying)
	{
		stateText.setString("STATE: FLYING");
	}
	else if (state == AircraftState::Landing)
	{
		float distance = getDistanceTo(runwayCenter);
		float ratio = distance / landingStartDistance;
		speed = landingStartSpeed * ratio;

		const float minSpeed = 2.f;
		if (speed < minSpeed && distance > 5.f)
			speed = minSpeed;

		if (distance < 1.f || distance <= speed * deltaTime)
		{
			position = runwayCenter;
			speed = 0.f;
			state = AircraftState::Landed;
			stateText.setString("STATE: LANDED");
		}
		else
		{
			stateText.setString("STATE: LANDING");
		}
	}
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
	stateText.setPosition(position + stateOffset);

	shapeAircraft.setFillColor(sf::Color::White);

	window.draw(shapeAircraft);
	window.draw(label);
	window.draw(speedText);
	window.draw(headingText);
	window.draw(destinationText);
	window.draw(stateText);
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

float Aircraft::getDistanceTo(sf::Vector2f targetPosition) {
	sf::Vector2f direction = targetPosition - position;

	float distance = std::sqrt(
		direction.x * direction.x +
		direction.y * direction.y
	);

	return distance;
}

bool Aircraft::isClicked(sf::Vector2i mousePosition) {
	float dx = mousePosition.x - position.x;
	float dy = mousePosition.y - position.y;
	float different = sqrt(dx * dx + dy * dy);
	
	return different <= 10.f;
}

bool Aircraft::isNear(sf::Vector2f targetPosition)
{
	sf::Vector2f direction = targetPosition - position;

	float distance = std::sqrt(
		direction.x * direction.x +
		direction.y * direction.y
	);

	return distance < 200.f;
}


sf::Vector2f Aircraft::getDirectionTo(sf::Vector2f targetPosition) {
	sf::Vector2f direction = targetPosition - position;
	return direction;
}


std::string Aircraft::getDestination() {
	return destination;
}