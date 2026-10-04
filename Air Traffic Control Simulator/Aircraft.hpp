#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

enum class AircraftState {
	Landed,
	Flying,
	Landing
};


class Aircraft
{
public:
	Aircraft(const std::string& newCallsign, sf::Vector2f position);

	void update(float deltaTime, float runwayHeading, sf::Vector2f runwayCenter);
	void draw(sf::RenderWindow& window);
	void setDestination(const std::string& newDestination);
	void setTCASWarning(bool warning);

	int getAltitude();

	float getSpeed();
	float getHeading();
	float getDistanceTo(sf::Vector2f targetPosition);

	bool isClicked(sf::Vector2i mousePosition);
	bool isNear(sf::Vector2f targetPosition);
	bool isTooClose(const Aircraft& other);

	std::string getDestination();

	sf::Vector2f getDirectionTo(sf::Vector2f targetPosition);
	sf::Vector2f getPosition();

private:
	AircraftState state = AircraftState::Flying;

	int altitude = 5000;
	int targetAltitude = 8000;

	float heading = 0.f;
	float speed = 50.f;
	float height = 0.f;
	float turnSpeed = 60.f;
	float acceleration = 30.f;
	float maxSpeed = 200.f;
	float landingStartSpeed = 0.f;
	float landingStartDistance = 0.f;

	std::string callsign = "NO123";
	std::string destination = "";

	sf::Vector2f position{ 600.f,400.f };
	sf::CircleShape shapeAircraft{ 3.f };

	sf::Font font;

	sf::Text label{ font };
	sf::Text speedText{ font };
	sf::Text headingText{ font };
	sf::Text destinationText{ font };
	sf::Text stateText{ font };
	sf::Text heightText{ font };
	sf::Text tcasWarningText{ font };

	sf::Vector2f textOffset{ 10.f, -30.f };        
	sf::Vector2f speedOffset{ 10.f, -15.f };
	sf::Vector2f headingOffset{ 10.f, -3.f };
	sf::Vector2f altitudeOffset{ 10.f, 9.f };
	sf::Vector2f destinationOffset{ 10.f, 21.f };
	sf::Vector2f stateOffset{ 10.f, 33.f };
	sf::Vector2f tcasWarningOffset{ 10.f, 45.f };
};

