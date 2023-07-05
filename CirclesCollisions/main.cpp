#include <SFML/Graphics.hpp>
#include "circle.h"
#include <vector>

using namespace std;

int main()
{
	srand(time(0));
	setlocale(0, "rus");

	Font font;
	font.loadFromFile("font.ttf");
	Text infoText;
	infoText.setCharacterSize(20);
	infoText.setFillColor(Color::Black);
	infoText.setFont(font);
	infoText.setPosition(0, 0);
	Clock gClock;

	circle* controllingCircle = nullptr;

	RenderWindow window(VideoMode(1280, 720), "SFML");
	//window.setVerticalSyncEnabled(true);
	vector<circle> objects;

	while (window.isOpen())
	{
		double gtime = gClock.getElapsedTime().asMicroseconds() / 1000.0;
		gClock.restart();
		Vector2i mousePos = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					objects.push_back(circle(mousePos.x, mousePos.y));
					controllingCircle = nullptr;
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					if (controllingCircle == nullptr) {
						for (auto iter = objects.begin(); iter < objects.end(); iter++) {
							if (pow(mousePos.x - iter->getPosition().x, 2) + pow(mousePos.y - iter->getPosition().y, 2) < pow(iter->getRadius(), 2)) {
								controllingCircle = &*iter;
								break;
							}
						}
					}
					else {
						controllingCircle = nullptr;
					}
			}
			}
			if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::R)) {
					objects.clear();
				}
			}
		}
		for (auto iter = objects.begin(); iter < objects.end(); iter++) iter->clearCalculatedFlag();
		if (controllingCircle != nullptr) {
			controllingCircle->setPosition(mousePos.x, mousePos.y);
		}
		for (auto iter = objects.begin(); iter < objects.end(); iter++) iter->update(window.getSize());

		window.clear(Color::White);
		for (auto iter = objects.begin(); iter < objects.end(); iter++) {
			iter->update(objects);
			iter->draw(window);
		}
		infoText.setString("FPS: " + std::to_string(1000.0 / gtime) + "\n" + L"Объектов: " + std::to_string(objects.size()));
		window.draw(infoText);
		window.display();
	}

	return 0;
}