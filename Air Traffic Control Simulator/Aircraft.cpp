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
	targetAltitude = altitude;
	targetSpeed = speed;
}

void Aircraft::update(float deltaTime,float runwayHeading, sf::Vector2f runwayCenter, bool isSelected)
{	
	if (state == AircraftState::Landed)
	{
		return;
	}
	if (altitude != targetAltitude)
	{
		if (altitude < targetAltitude)
		{
			altitude += climbRate * deltaTime;
			if (altitude > targetAltitude)
				altitude = targetAltitude;
		}
		else if (altitude > targetAltitude)
		{
			altitude -= descentRate * deltaTime;
			if (altitude < targetAltitude)
				altitude = targetAltitude;
		}

		if (std::abs(altitude - targetAltitude) < 1.f)
		{
			altitude = targetAltitude;
			tcasResolution = TCASResolution::None;
		}
	}

	if (!isManualControl && state == AircraftState::Flying && isNear(runwayCenter))
	{
		state = AircraftState::Landing;
		landingStartSpeed = speed;
		landingStartDistance = getDistanceTo(runwayCenter);
	}


	if (!isManualControl)
	{
		sf::Vector2f directionToTarget = getDirectionTo(runwayCenter);
		float angle = std::atan2(directionToTarget.x, -directionToTarget.y);
		targetHeading = angle * 180.f / std::numbers::pi_v<float>;

		if (targetHeading < 0.f)
			targetHeading += 360.f;
	}

	
	
	if (state == AircraftState::Flying)
	{
		stateText.setString("STATE: FLYING");
		stateText.setFillColor(flyingColor);

		if (speed < targetSpeed)
		{
			speed += acceleration * deltaTime;
			if (speed > targetSpeed)
				speed = targetSpeed;
		}
		else if (speed > targetSpeed)
		{
			speed -= acceleration * deltaTime;
			if (speed < targetSpeed)
				speed = targetSpeed;
		}
	}
	else if (state == AircraftState::Landing)
	{
		float distance = getDistanceTo(runwayCenter);
		float ratio = distance / landingStartDistance;
		speed = landingStartSpeed * ratio;

		const float minSpeed = 3.5f;
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

	if (isSelected)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			isManualControl = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		{
			targetAltitude += climbRate * deltaTime;
			if (targetAltitude > 35000.f)
			{
				targetAltitude = 35000.f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		{
			targetAltitude -= climbRate * deltaTime;
			if (targetAltitude < 1000.f)
			{
				targetAltitude = 1000.f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			isManualControl = true;
			targetHeading -= turnSpeed * deltaTime;
			if (targetHeading < 0.f)
				targetHeading += 360.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			isManualControl = true;
			targetHeading += turnSpeed * deltaTime;
			if (targetHeading >= 360.f)
				targetHeading -= 360.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			targetSpeed += acceleration * deltaTime;
			if (targetSpeed > maxSpeed)
				targetSpeed = maxSpeed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			targetSpeed -= acceleration * deltaTime;
			if (targetSpeed < 0.f)
				targetSpeed = 0.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
		{
			state = AircraftState::Flying;
			targetSpeed = 70.f;
			isManualControl = true;
			targetAltitude = 3000.f;
		}
	}
	
	float difference = targetHeading - heading;
	if (difference > 180.f)
		difference -= 360.f;

	if (difference < -180.f)
		difference += 360.f;
	float step = turnSpeed * deltaTime;

	if (std::abs(difference) <= step)
		heading = targetHeading;
	else
		heading += (difference > 0.f ? step : -step);

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

	if (state != AircraftState::Landed)
	{
		float radians = heading * std::numbers::pi_v<float> / 180.f;
		sf::Vector2f direction(std::sin(radians), -std::cos(radians));

		float lookaheadSeconds = 5.f;
		sf::Vector2f vectorEnd = position + direction * (speed * lookaheadSeconds);

		sf::Vertex line[] = {
			sf::Vertex{position, sf::Color(100, 220, 140, 180)},
			sf::Vertex{vectorEnd, sf::Color(100, 220, 140, 40)}
		};

		window.draw(line, 2, sf::PrimitiveType::Lines);
	}

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

	if (std::abs(altitude - targetAltitude) > 10.f)
	{
		heightText.setString("ALT: " + std::to_string(static_cast<int>(altitude)) +
			" -> " + std::to_string(static_cast<int>(targetAltitude)));
	}
	else
	{
		heightText.setString("ALT: " + std::to_string(static_cast<int>(altitude)) + " ft");
	}


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

void Aircraft::setTCASResolution(TCASResolution resolution)
{
	if (resolution == TCASResolution::None) return;
	if (tcasResolution != TCASResolution::None) return;

	tcasResolution = resolution;
	targetAltitude = altitude + (resolution == TCASResolution::Climb ? 1000.f : -1000.f);
}
void Aircraft::setTargetAltitude(float newTargetAltitude) {
	targetAltitude = newTargetAltitude;
}

float Aircraft::getSpeed()
{
	return speed;
}

float Aircraft::getHeading()
{
	return heading;
}

float Aircraft::getAltitude() {
	return altitude;
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
	float different = std::sqrt(dx * dx + dy * dy);
	
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
