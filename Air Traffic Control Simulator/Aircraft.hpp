#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Aircraft
{
public:
	Aircraft();
	
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	float getSpeed();
	float getHeading();

	

private:
	float speed = 50.f;
	float heading = 0.f;
	float turnSpeed = 60.f;
	float acceleration = 30.f;
	float maxSpeed = 200.f;
	float deltaSpeed = 0.f;

	std::string callsign = "NO123";

	sf::Vector2f position{600.f,400.f};
	sf::CircleShape shapeAircraft{3.f};
	
	sf::Font font;
	
	sf::Text label{font};
	sf::Text speedText{font};
	sf::Text headingText{font};

	sf::Vector2f textOffset{ -20.f, -55.f };
	sf::Vector2f speedOffset = { -25.f, -38.f };
	sf::Vector2f headingOffset = { -25.f, -21.f };

};

