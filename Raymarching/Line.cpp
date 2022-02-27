#include "functions.h"

line::line(sf::Vector2f p, sf::Vector2f P) {
	p1 = p;
	p2 = P;

	grad = (p1.y - p2.y) / (p1.x - p2.x);
	yInte = p1.x * grad + p1.y;
}

float line::returnPerpGrad() {
	return -1 * (1 / grad);
}

bool line::checkInLine(sf::Vector2f p) {
	return p.y == p.x * grad + yInte;
}
