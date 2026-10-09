#include <iostream>
#include <vector>
#include <numbers>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Aircraft.hpp"
#include "Airport.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "ATC Simulator", sf::Style::Titlebar);
	sf::Clock clock;
	sf::Vector2i mousePosition;

	std::vector<Aircraft> aircrafts;
	Airport airport1("LZIB", { 200.f,600.f });
	Airport airport2("LZIT", { 900.f,150.f });
 
	aircrafts.reserve(3);
	aircrafts.emplace_back("MA345", sf::Vector2f{ 300.f,400.f });
	aircrafts.emplace_back("NO123", sf::Vector2f{ 800.f,200.f });
	aircrafts.emplace_back("BA875", sf::Vector2f{ 1000.f,600.f });

	aircrafts[0].setDestination("LZIB");
	aircrafts[1].setDestination("LZIB");
	aircrafts[2].setDestination("LZIT");

	int selectedAircraft = 0;


	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
				
				if (mouse->button == sf::Mouse::Button::Left)
				{
					mousePosition = mouse->position;
				}
			}
		}
		
		window.clear(sf::Color(10, 15, 25));

		
		for (int i = 0; i < aircrafts.size(); i++)
		{
			if (aircrafts[i].isClicked(mousePosition))
			{
				selectedAircraft = i;
			}
		}

		for (auto& aircraft : aircrafts)
		{
			aircraft.setTCASLevel(TCASLevel::Clear);
		}

		for (size_t i = 0; i < aircrafts.size(); i++)
		{
			for (size_t j = i + 1; j < aircrafts.size(); j++)
			{
				float distance = aircrafts[i].getDistanceTo(aircrafts[j].getPosition());

				if (aircrafts[i].isTooClose(aircrafts[j]))
				{
					int altitudeDifference = std::abs(aircrafts[i].getAltitude() - aircrafts[j].getAltitude());

					if (distance < 20 && altitudeDifference < 500)
					{
						aircrafts[i].setTCASLevel(TCASLevel::Collision);
						aircrafts[j].setTCASLevel(TCASLevel::Collision);
					}
					else if (distance < 50 && altitudeDifference < 500)
					{
						aircrafts[i].setTCASLevel(TCASLevel::RA);
						aircrafts[j].setTCASLevel(TCASLevel::RA);

						if (aircrafts[i].getAltitude() >= aircrafts[j].getAltitude())
						{
							aircrafts[i].setTCASResolution(TCASResolution::Climb);
							aircrafts[j].setTCASResolution(TCASResolution::Descend);
						}
						else
						{
							aircrafts[i].setTCASResolution(TCASResolution::Descend);
							aircrafts[j].setTCASResolution(TCASResolution::Climb);
						}
					}
					else if (distance < 100 && altitudeDifference < 1000)
					{
						aircrafts[i].setTCASLevel(TCASLevel::TA);
						aircrafts[j].setTCASLevel(TCASLevel::TA);
					}
				}
			}
		}



		for (int i = 0; i < aircrafts.size(); i++)
		{
			bool isSelected = (i == selectedAircraft);

			if (aircrafts[i].getDestination() == "LZIB")
			{
				aircrafts[i].update(
					deltaTime,
					airport1.getRunwayHeading(),
					airport1.getCenterOfRunway(),
					isSelected
				);
			}
			else if (aircrafts[i].getDestination() == "LZIT")
			{
				aircrafts[i].update(
					deltaTime,
					airport2.getRunwayHeading(),
					airport2.getCenterOfRunway(),
					isSelected
				);
			}

			aircrafts[i].draw(window);
		}
		airport1.drawAirport(window);
		airport2.drawAirport(window);

		window.display();
	}

	return 0;
}