#include "functions.h"

Point::Point(sf::Vector2f p, float r) {

	rep.setRadius(r);
	rep.setOrigin(sf::Vector2f(r, r));
	rep.setFillColor(sf::Color::Green);
	rep.setPosition(conv(p));

	pos = p;
}

Point::Point() {
	rep.setRadius(0);
	pos = sf::Vector2f();
}

void Point::move(sf::Vector2f p) {
	pos = p;
	rep.setPosition(pos);
}
