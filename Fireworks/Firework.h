#pragma once
#include <SFML\Graphics.hpp>
#include "Particle.h"
#include <iostream>
#include <random>
#include <memory>
class Firework
{
public:
	std::shared_ptr<Particle> firework;
	std::vector<std::shared_ptr<Particle>> explosion;
	bool exploded = false;
	bool fireworkbom = false;
	bool done = false;
	float col;
public:
	Firework(int, int);
	~Firework();
	void show(sf::RenderWindow &, sf::Vector2f);
	void explode();

};

