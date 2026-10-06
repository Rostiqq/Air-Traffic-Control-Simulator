#include "Aircraft.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <numbers>

namespace
{
	const sf::Color textMain(220, 230, 235);
	const sf::Color textSecondary(145, 160, 175);
	const sf::Color callsignColor(100, 220, 140);

	const sf::Color flyingColor(220, 230, 235);
	const sf::Color landingColor(255, 200, 70);
	const sf::Color landedColor(100, 220, 140);
}

Aircraft::Aircraft(const std::string& newCallsign, sf::Vector2f position) : label(font) {
	if (!font.openFromFile("GeistMono-Regular.ttf"))
	{
		std::cout << "Font sa nepodarilo nacitat!\n";
	}

	label.setCharacterSize(13);
	speedText.setCharacterSize(10);
	headingText.setCharacterSize(10);
	destinationText.setCharacterSize(10);
	stateText.setCharacterSize(10);
	heightText.setCharacterSize(10);
	tcasWarningText.setCharacterSize(12);

	tcasWarningText.setFillColor(sf::Color::Red);
	label.setFillColor(callsignColor);
	speedText.setFillColor(textSecondary);
	headingText.setFillColor(textSecondary);
	heightText.setFillColor(textSecondary);
	destinationText.setFillColor(textSecondary);
	stateText.setFillColor(textMain);
	shapeAircraft.setFillColor(sf::Color::White);

	shapeAircraft.setOrigin({ 3.f, 3.f });

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
		stateText.setFillColor(flyingColor);
	}
	else if (state == AircraftState::Landing)
	{
		float distance = getDistanceTo(runwayCenter);
		float ratio = distance / landingStartDistance;
		speed = landingStartSpeed * ratio;

		const float minSpeed = 3.5;
		if (speed < minSpeed && distance > 5.f)
			speed = minSpeed;

		if (distance < 1.f || distance <= speed * deltaTime)
		{
			position = runwayCenter;
			speed = 0.f;
			state = AircraftState::Landed;
			stateText.setString("STATE: LANDED");
			stateText.setFillColor(landedColor);
		}
		else
		{
			stateText.setString("STATE: LANDING");
			stateText.setFillColor(landingColor);
		}
	}
	float currentHeading = getHeading();
	float difference = targetHeading - currentHeading;

	if (difference > 180.f)
		difference -= 360.f;

	if (difference < -180.f)
		difference += 360.f;

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
			heading = 0.f;
		}

	}



	//if (difference > 0)
	//	heading += turnSpeed * deltaTime;
	//else if (difference < 0)
	//{
	//	heading -= turnSpeed * deltaTime;
	//}
	
	if (heading >= 360.f)
	{
		heading -= 360.f;
	}
	else if (heading < 0.f)
	{
		heading += 360.f;
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
	
}

void Aircraft::draw(sf::RenderWindow& window) {
	switch (tcasLevel)
	{
	case TCASLevel::Clear:
		tcasWarningText.setString("");
		break;

	case TCASLevel::TA:
		tcasWarningText.setString("TCAS: TRAFFIC");
		break;

	case TCASLevel::RA:
		tcasWarningText.setString("TCAS: RA");
		break;

	case TCASLevel::Collision:
		tcasWarningText.setString("TCAS: COLLISION");
		break;
	}
	
	shapeAircraft.setPosition(position);
	label.setPosition(position + textOffset);
	speedText.setPosition(position + speedOffset);
	headingText.setPosition(position + headingOffset);
	destinationText.setPosition(position + destinationOffset);
	stateText.setPosition(position + stateOffset);
	heightText.setPosition(position + altitudeOffset);
	tcasWarningText.setPosition(position + tcasWarningOffset);

	heightText.setString("ALT: " + std::to_string(altitude) + " ft");

	window.draw(shapeAircraft);
	window.draw(label);
	window.draw(speedText);
	window.draw(headingText);
	window.draw(destinationText);
	window.draw(stateText);
	window.draw(heightText);
	window.draw(tcasWarningText);
}

void Aircraft::setDestination(const std::string& newDestination) {
	destination = newDestination;
	destinationText.setString("DEST: " + destination);
}

void Aircraft::setTCASLevel(TCASLevel level)
{
	tcasLevel = level;
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

bool Aircraft::isTooClose(const Aircraft& other) {
	float dx = position.x - other.position.x;
	float dy = position.y - other.position.y;

	float distance = std::sqrt(dx * dx + dy * dy);

	return distance < 200.f;
}

sf::Vector2f Aircraft::getDirectionTo(sf::Vector2f targetPosition) {
	sf::Vector2f direction = targetPosition - position;
	return direction;
}

sf::Vector2f Aircraft::getPosition() {
	return position;
}


std::string Aircraft::getDestination() {
	return destination;
}

int Aircraft::getAltitude() {
	return altitude;
}