#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Airport
{
public:
	void drawAirport(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	Airport();

private:
	std::string airportCode = "LZIB";
	std::string runwayNumber = "09";

	sf::Vector2f airportPosition = { 150,550 };
	sf::Vector2f runwayPosition = airportPosition + sf::Vector2f{ 36.f, 0.f };

	sf::RectangleShape airportShape;
	sf::RectangleShape runway;

	sf::Font font;
	sf::Text label{ font };
	sf::Text runwayLabel{ font };
};
