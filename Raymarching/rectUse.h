#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "functions.h"

class rectUse {
public:
	sf::RectangleShape self;

	Point p1;
	Point p2;
	Point p3;
	Point p4;
	Point p5;

	bool drawingCorners;

	rectUse(sf::Vector2f size, sf::Vector2f pos, float rot, sf::Color oCol);
	void outputBounds();
	void draw(sf::RenderWindow& window);
};
