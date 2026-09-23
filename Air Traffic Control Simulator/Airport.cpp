#include "Airport.hpp"
#include <iostream>

Airport::Airport() {

	if (!font.openFromFile("GeistMono-Regular.ttf"))
	{
		std::cout << "Nepodarilo sa nacitat font.\n";
	}

	label.setCharacterSize(15);
	label.setString(airportCode);
	runwayLabel.setCharacterSize(10);
	runwayLabel.setString(runwayNumber);
}

void Airport::drawAirport(sf::RenderWindow& window) {
	airportShape.setSize({ 50.f, 100.f });
	airportShape.setPosition(airportPosition);
	airportShape.setFillColor(sf::Color(25, 35, 50));

	label.setPosition(airportPosition + sf::Vector2f({ 5.f,-25.f }));
	label.setFillColor(sf::Color(180, 200, 220));

	runway.setSize({ 20.f,120.f });
	runway.setPosition(runwayPosition);
	runway.setFillColor(sf::Color(120, 130, 140));

	runwayLabel.setOrigin(runwayLabel.getLocalBounds().getCenter());
	runwayLabel.setPosition(runwayPosition + runway.getSize() / 2.f);
	runwayLabel.setFillColor(sf::Color(25, 35, 50));

	window.draw(airportShape);
	window.draw(runway);
	window.draw(label);
	window.draw(runwayLabel);
}

