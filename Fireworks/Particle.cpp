#include "Particle.h"


float Umap(float value, float istart, float istop, float ostart, float ostop) {
	return ostart + (ostop - ostart)*((value - istart) / (istop - istart));
}

double unirand(float start, float end) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(start, end);
	return dist(mt);
}

Particle::Particle() {
	Particle(200, 800, true, 255);
}
Particle::Particle(float x, float y, bool fw, float coli)
{
	done = false;
	col = coli;
	point.setRadius(8);
	lifespan = 255;
	isfir = fw;
	this->pos.x = x;
	this->pos.y = y;
	if (isfir) {
		this->vel.y = unirand(1.2, 1.9);
		this->vel.y *= -1;
	}
	else {
		this->vel.y = unirand(-1.0, 1.0);
		this->vel.x = unirand(-1.0, 1.0);
	}
}


Particle::~Particle()
{
}

void Particle::update() {
	if (!isfir) {
		//vel *= 0.998f;
		acc.y += 0.0001;
		lifespan -= 1;
		point.setRadius(4);
		this->point.setFillColor((setColor(col, 1, 1, lifespan)));
	}
	this->vel += this->acc;
	this->pos += this->vel;
	this->acc *= 0.f;
	if (lifespan <= 0) { done = true; }
}

void Particle::applyForce(sf::Vector2f force) {
	this->acc += force;
}

void Particle::show(sf::RenderWindow &target) {


	point.setPosition(this->pos);
	target.draw(point);
}


sf::Color Particle::setColor(int hue, float sat, float val, int alp) {

	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val*(1.f - sat);
	float q = val*(1.f - sat*f);
	float t = val*(1.f - sat*(1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255, alp);
	case 1: return sf::Color(q * 255, val * 255, p * 255, alp);
	case 2: return sf::Color(p * 255, val * 255, t * 255, alp);
	case 3: return sf::Color(p * 255, q * 255, val * 255, alp);
	case 4: return sf::Color(t * 255, p * 255, val * 255, alp);
	case 5: return sf::Color(val * 255, p * 255, q * 255, alp);
	}
}
