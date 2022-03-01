#include "functions.h"

line::line(sf::Vector2f p, sf::Vector2f P) {
	//line with points
	p1 = p;
	p2 = P;

	grad = (p1.y - p2.y) / (p1.x - p2.x);
	yInte = p1.x * grad + p1.y;
}

line::line(float m, float c) : p1(sf::Vector2f(0, 0)), p2(sf::Vector2f(0, 0)){
	//line with undefined points
	grad = m;
	yInte = c;

}

float line::returnPerpGrad() {
	return -1 * (1 / grad);
}

bool line::checkInLine(sf::Vector2f p) {
	return p.y == p.x * grad + yInte;
}

sf::Vector2f line::returnIntersect(line l) {
	float x = l.grad - grad;
	float c = yInte - l.yInte;

	x = c / x;

	return sf::Vector2f(x, x * grad + yInte);
}
