#pragma once
#include "functions.h"

class rectUse {
public:
	sf::RectangleShape self;


	std::vector<sf::Vector2f> corners;

	float rotation;

	rectUse(float width, sf::Vector2f pos, float rot, sf::Color oCol);
	void outputBounds();
	void draw(sf::RenderWindow& window);
};
