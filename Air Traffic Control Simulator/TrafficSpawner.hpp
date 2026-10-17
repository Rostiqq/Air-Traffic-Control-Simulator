#pragma once
#include <string>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Aircraft.hpp"

class TrafficSpawner 
{
public:
	TrafficSpawner(float spawnerIntervalSeconds);

	void update(float deltaTime, std::vector<Aircraft>& aircrafts);
	sf::Vector2f getRandomSpawnPosition();

	std::string getRandomCallsign();
	std::string getRandomDestination();

private:
	float spawnInterval = 15.f;
	float timer = 0.f;

	std::vector<std::string> airlines = { "RYR", "WZZ", "DLH", "AUA", "EJU", "LOT", "BAW" };
	std::vector<std::string> destinations = { "LZIB", "LZIT" };

	std::mt19937 rng;
};

