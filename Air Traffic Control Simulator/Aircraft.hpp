#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Aircraft
{
public:
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	float speed = 50.f;
	float heading = 0.f;
	float turnSpeed = 60.f;
	sf::Vector2f position{600.f,400.f};

	sf::CircleShape shapeAircraft{3.f};
	
};

