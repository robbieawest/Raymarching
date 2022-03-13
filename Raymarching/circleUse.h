#pragma once
#include "functions.h"

class circleUse {
public:
	sf::CircleShape self;
	circleUse(float r, sf::Vector2f pos, sf::Color col, int opacity);
	void draw(sf::RenderWindow& window);
};
