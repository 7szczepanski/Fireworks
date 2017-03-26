#pragma once
#include <SFML\Graphics.hpp>
#include <random>
#include <iostream>

class Particle
{
public:
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f acc;
	sf::CircleShape point;
	bool isfir;
	bool done;
	int lifespan;
	float col;
public:
	Particle();
	Particle(float, float, bool, float);
	~Particle();
	void update();
	void applyForce(sf::Vector2f);
	void show(sf::RenderWindow &);
	sf::Color setColor(int, float, float, int);
};

