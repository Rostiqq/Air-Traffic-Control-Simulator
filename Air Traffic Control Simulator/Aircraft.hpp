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

	void update(float deltaTime,float runwayHeading,sf::Vector2f runwayCenter);
	void draw(sf::RenderWindow& window);
	void setDestination(const std::string& newDestination);

	float getSpeed();
	float getHeading();
	float getDistanceTo(sf::Vector2f targetPosition);

	bool isClicked(sf::Vector2i mousePosition);
	bool isNear(sf::Vector2f targetPosition);

	std::string getDestination();

	sf::Vector2f getDirectionTo(sf::Vector2f targetPosition);

private:
	AircraftState state = AircraftState::Flying;


	float speed = 50.f;
	float heading = 0.f;
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

	sf::Vector2f textOffset{ -20.f, -55.f };
	sf::Vector2f speedOffset = { -25.f, -38.f };
	sf::Vector2f headingOffset = { -25.f, -21.f };
	sf::Vector2f destinationOffset = { -25.f,10.f };
	sf::Vector2f stateOffset = { -25.f,25.f };

};

