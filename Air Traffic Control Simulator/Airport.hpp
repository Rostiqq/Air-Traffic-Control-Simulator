#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Airport
{
public:
	Airport(std::string airportNewCode, sf::Vector2f position);
	
	void drawAirport(sf::RenderWindow& window);

	sf::Vector2f getPosition();

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
