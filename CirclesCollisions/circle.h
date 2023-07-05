#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class circle
{
private:
	CircleShape obj;
	bool calculated = false;
public:
	circle();
	circle(float r);
	circle(float x, float y);
	circle(float x, float y, float r);
	circle(float x, float y, float r, Color color);

	void clearCalculatedFlag();
	bool getCalculatedFlag();
	void setPosition(float _x, float _y);
	void setRadius(float _r);
	Vector2f getPosition();
	float getRadius();
	void update(std::vector<circle>& objects);
	void update(Vector2u borderSize);
	void draw(RenderWindow &window);
};

