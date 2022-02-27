#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "functions.h"


class Point {
public:

	sf::CircleShape rep;
	sf::Vector2f pos;

	Point(sf::Vector2f p, float r);
	Point();
	void move(sf::Vector2f p);

};
