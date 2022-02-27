#include "functions.h"

class line {
public:

	sf::Vector2f p1;
	sf::Vector2f p2;
	float grad;
	float yInte;

	line(sf::Vector2f p, sf::Vector2f P);
	float returnPerpGrad();
	bool checkInLine(sf::Vector2f p);
};
