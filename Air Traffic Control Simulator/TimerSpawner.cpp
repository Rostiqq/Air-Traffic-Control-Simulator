#include <vector>
#include <string>
#include <random>
#include <SFML/Graphics.hpp>
#include "TrafficSpawner.hpp"

TrafficSpawner::TrafficSpawner(float spawnerIntervalSeconds) {
	spawnInterval = spawnerIntervalSeconds;
	rng.seed(std::random_device{}());
}

void TrafficSpawner::update(float deltaTime, std::vector<Aircraft>& aircrafts) {
	timer += deltaTime;
	if (timer >= spawnInterval)
	{
		timer = 0.f;
		aircrafts.emplace_back(getRandomCallsign(), getRandomSpawnPosition());
		aircrafts.back().setDestination(getRandomDestination());
	}
}

std::string TrafficSpawner::getRandomCallsign() {
	std::uniform_int_distribution<size_t> airlineDist(0, airlines.size() - 1);
	std::uniform_int_distribution<int> flightNumDist(100, 999);

	std::string randomAirline = airlines[airlineDist(rng)];
	int randomNumber = flightNumDist(rng);

	return randomAirline + std::to_string(randomNumber);
}

std::string TrafficSpawner::getRandomDestination() {
	std::uniform_int_distribution<size_t> destineDist(0, destinations.size() - 1);
	std::string randomDestination = destinations[destineDist(rng)];
	return randomDestination;
}

sf::Vector2f TrafficSpawner::getRandomSpawnPosition() {
	std::uniform_int_distribution<int> sideDist(0, 3);
	std::uniform_real_distribution<float> xDist(50.f, 1150.f);
	std::uniform_real_distribution<float> yDist(50.f, 750.f);

	int side = sideDist(rng);

	switch (side) {
	case 0: 
		return sf::Vector2f(xDist(rng), 0.f);
	case 1: 
		return sf::Vector2f(xDist(rng), 800.f);
	case 2: 
		return sf::Vector2f(0.f, yDist(rng));
	case 3: 
	default:
		return sf::Vector2f(1200.f, yDist(rng));
	}
}