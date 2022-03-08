#include "functions.h"

class line {
public:

	//Short line is the line from p1 -> p2
	//Full line is the mathematical representation of the line y = mx + c where m = grad, c = yInte
	sf::Vector2f p1;
	sf::Vector2f p2;
	float grad;
	float yInte;

	line(sf::Vector2f p, sf::Vector2f P);
	line(float m, float c);

	float returnPerpGrad();
	bool checkInLine(sf::Vector2f p, sf::Vector2f p1);
	bool checkInSmallLine(sf::Vector2f p, sf::Vector2f p1);

	sf::Vector2f returnIntersect(line l, sf::Vector2f p1, sf::Vector2f p2);
};
