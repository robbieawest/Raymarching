#pragma once
#include "functions.h"

class circleUse {
public:
	sf::CircleShape self;
//	Point p1;
//	Point p2;
//	Point p3;

	circleUse(float r, sf::Vector2f pos, sf::Color col);
	void draw(sf::RenderWindow& window);
};
