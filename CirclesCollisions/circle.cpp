#include "circle.h"
#include <iostream>

circle::circle()
{
	obj.setRadius(rand() % 30 + 10);
	obj.setPosition(0.0f, 0.0f);
	obj.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
}

circle::circle(float r)
{
	obj.setRadius(r);
	obj.setPosition(0.0f, 0.0f);
	obj.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
}

circle::circle(float x, float y)
{
	float radius = rand() % 30 + 10;
	obj.setRadius(radius);
	obj.setOrigin(radius, radius);
	obj.setPosition(x, y);
	obj.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
}

circle::circle(float x, float y, float r)
{
	obj.setRadius(r);
	obj.setOrigin(r / 2.0f, r / 2.0f);
	obj.setPosition(x, y);
	obj.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
}

circle::circle(float x, float y, float r, Color color)
{
	obj.setRadius(r);
	obj.setOrigin(r, r);
	obj.setPosition(x, y);
	obj.setFillColor(color);
}

void circle::clearCalculatedFlag()
{
	calculated = false;
}

bool circle::getCalculatedFlag()
{
	return calculated;
}

void circle::setPosition(float _x, float _y)
{
	obj.setPosition(_x, _y);
	calculated = true;
}

void circle::setRadius(float _r)
{
	obj.setRadius(_r);
}

Vector2f circle::getPosition()
{
	return obj.getPosition();
}

float circle::getRadius()
{
	return obj.getRadius();
}

void circle::update(std::vector<circle>& objects)
{
	Vector2f sumForces(0.0f, 0.0f);
	if (this->calculated) {
		for (auto iter = objects.begin(); iter < objects.end(); iter++) {
			if (&*iter != this) {
				double dis = sqrt((iter->getPosition().x - this->getPosition().x) * (iter->getPosition().x - this->getPosition().x) + (iter->getPosition().y - this->getPosition().y) * (iter->getPosition().y - this->getPosition().y));
				if (dis != 0.0f)
					if (iter->getRadius() + this->getRadius() > dis + 1.0f) {
						Vector2f norm = Vector2f((this->obj.getPosition().x - iter->getPosition().x) / dis * (dis - iter->getRadius() - this->getRadius()), (this->obj.getPosition().y - iter->getPosition().y) / dis * (dis - iter->getRadius() - this->getRadius()));
						if (iter->getCalculatedFlag()) {

							sumForces -= norm;

						}
						else {

							sumForces -= norm / 2.0f;

						}
						if (sumForces != Vector2f(0.0f, 0.0f)) sumForces /= 2.0f;

					}
			}
		}
		this->obj.move(sumForces);
	}
	this->calculated = true;
}

void circle::update(Vector2u borderSize)
{
	if (this->getRadius() + this->getPosition().x > borderSize.x) {
		this->obj.move(borderSize.x - this->getRadius() - this->getPosition().x, 0);
	}
	if (this->getPosition().x - this->getRadius() < 0) {
		this->obj.move(this->getRadius() - this->getPosition().x, 0);
	}

	if (this->getRadius() + this->getPosition().y > borderSize.y) {
		this->obj.move(0, borderSize.y - this->getRadius() - this->getPosition().y);
	}
	calculated = true;
}

void circle::draw(RenderWindow& window)
{
	window.draw(obj);
}
