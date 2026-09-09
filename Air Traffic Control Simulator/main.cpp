#include <iostream>
#include <vector>
#include <numbers>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {

	sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "ATC Simulator", sf::Style::Titlebar);
	sf::Clock clock;

	sf::CircleShape aircraft(3);
	aircraft.setFillColor(sf::Color::White);
	aircraft.setPosition({ 300,300 });

	sf::Vector2f position({ 600.f,400.f });
	float speed = 50.f;
	float heading = 0.f;

	float turnSpeed = 60.f;

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();


		}

		

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




		float radians = heading * std::numbers::pi_v<float> / 180.f;

		sf::Vector2f direction(std::sin(radians), -std::cos(radians));
		position += direction * speed * deltaTime;




		window.clear(sf::Color(10, 15, 25));
		aircraft.setPosition(position);
		window.draw(aircraft);
		window.display();

		std::cout << "\rheading: " << heading << "    speed: " << speed << std::flush;
	}

	return 0;
}