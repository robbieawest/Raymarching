#include "functions.h"

line::line(sf::Vector2f p, sf::Vector2f P) {
	//line with points(with short line)
	p1 = p;
	p2 = P;

	grad = (p1.y - p2.y) / (p1.x - p2.x); //calculate m and c from points 
	yInte = -p1.x * grad + p1.y; //y - b = m(x - a) , y = mx + c, c = -ma + b
}

line::line(float m, float c) : p1(sf::Vector2f(0, 0)), p2(sf::Vector2f(0, 0)){
	//line with undefined points(just mathematical representation)
	grad = m;
	yInte = c;
}

float line::returnPerpGrad() {
	if (isinf(grad)) {
		return 0;
	}

	return -1 * (1 / grad);
}

bool line::checkInLine(sf::Vector2f p, sf::Vector2f p1) {
	//Function to check if a point coincides with the full line

	if (isinf(grad) || grad == 0.0f) {

		if (isinf(grad)) 
			return p.x == p1.x;		
		else
			return (p.y == p1.y && grad == 0.0f);
		

	}


	//This is not tested
	return p.y == p.x * grad + yInte;
}

bool line::checkInSmallLine(sf::Vector2f p, sf::Vector2f p1) {
	//p1 is to help for infinite and 0 values by providing example point
	//Function to check if a point coincides with the short line


	bool one = checkInLine(p, p1);
	bool two = IN_RANGE(p1, p2, p);


	return one && two;
}

sf::Vector2f line::returnIntersect(line l, sf::Vector2f p1, sf::Vector2f p2) {
	//return intersect of two mathematical representations of lines(which arent the same line, and do not have the same gradient, or it will not work)


	if (isinf(grad) || isinf(l.grad) || l.grad == 0.0f || grad == 0.0f) {
		bool one = l.grad == 0.0f;
		bool two = grad == 0.0f;

		return sf::Vector2f((isinf(grad) * p1.x) +
							(isinf(l.grad) * p2.x),
							(one * p2.y) +
							(two * p1.y)); //just conditions, no if statements so is faster(branchless)

	}
	float x = l.grad - grad;
	float c = yInte - l.yInte;

	x = c / x;

	return sf::Vector2f(x, x * grad + yInte);
}
