#include "Firework.h"

double unirandi(float start, float end) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(start, end);


	return dist(mt);
}


using namespace std;

Firework::Firework(int width, int height)
{

	shared_ptr<Particle> f(new Particle((int)unirandi(1, width), height - 1, true, col));
	firework = f;
	col = (int)unirandi(1, 360);


}


Firework::~Firework()
{
}

void Firework::show(sf::RenderWindow &target, sf::Vector2f gravity) {
	if (firework->vel.y >= 0) {
		exploded = true;
		explode();
	}
	if (!exploded) {
		firework->applyForce(gravity);
		firework->update();
		firework->show(target);
	}

	for (int i = explosion.size() - 1; i >= 0; i--) {
		explosion[i]->applyForce(gravity);
		explosion[i]->update();
		explosion[i]->show(target);
		if (explosion[i]->done) {
			explosion.erase(explosion.begin() + i);
		}
	}

	if (exploded&&explosion.size() == 0) {
		done = true;
	}
}

void Firework::explode() {
	if (exploded && !fireworkbom) {
		for (int i = 0; i < (int)unirandi(25, 200); i++) {
			shared_ptr<Particle> p(new Particle(this->firework->pos.x, this->firework->pos.y, false, col));
			explosion.push_back(p);
		}
		fireworkbom = true;
	}
}