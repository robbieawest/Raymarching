#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "functions.h"

class circleUse {
public:
	sf::CircleShape self;

	circleUse(float r, sf::Vector2f pos, sf::Color col);
	void draw(sf::RenderWindow& window);
};
