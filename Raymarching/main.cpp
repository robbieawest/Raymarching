#include <SFML/Graphics.hpp>
#include <iostream>

int windowWidth = 1200;
int windowHeight = 800;

sf::Vector2f conv(sf::Vector2f v) {
	return sf::Vector2f(v.x, windowHeight - v.y);
}

class Point {
public:

	sf::CircleShape rep;
	sf::Vector2f pos;


	Point(sf::Vector2f p, float r) {

		rep.setRadius(r);
		rep.setOrigin(sf::Vector2f(r / 2.0f, r / 2.0f));
		rep.setFillColor(sf::Color::Green);
		rep.setPosition(conv(p));

		pos = p;
	}

	void move(sf::Vector2f p) {
		pos = p;
		rep.setPosition(pos);
	}

};


int main() {

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Raymarching", sf::Style::Default);

	Point p = Point(sf::Vector2f(200, 300), 10);

	

	while (window.isOpen()) {
		sf::Event evnt;

		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		sf::Vector2i mP = sf::Mouse::getPosition(window);
		p.move(sf::Vector2f(float(mP.x), float(mP.y)));


		window.clear();

		window.draw(p.rep);

		window.display();
	}

	return 0;
}