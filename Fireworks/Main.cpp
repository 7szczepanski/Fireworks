#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <time.h>
#include "Particle.h"
#include "Firework.h"


sf::Vector2f gravity = sf::Vector2f(0, 0.002);


int main()
{
	srand(time(NULL));
	int width = 1200;
	int height = 800;
	std::vector<Firework> fireworks;
	sf::RenderWindow window(sf::VideoMode(width, height), "Fireworks");
	window.setFramerateLimit(90);
	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setFillColor(sf::Color(0, 0, 0));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (rand() % 110 + 1 == 3) {
			Firework firework(width, height);
			fireworks.push_back(firework);
		}

		window.clear();
		window.draw(background);

		for (int i = fireworks.size() - 1; i > 0; i--) {
			fireworks[i].show(window, gravity);
			if (fireworks[i].firework->vel.y >= 0) {
				if (fireworks[i].fireworkbom == false) {
					fireworks[i].explode();
				}
				if (fireworks[i].done) {
					fireworks.erase(fireworks.begin() + i);
				}
			}
		}
		window.display();
	}

	return 0;
}