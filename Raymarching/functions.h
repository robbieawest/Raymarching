#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


int windowWidth = 1200;
int windowHeight = 800;



sf::Vector2f conv(sf::Vector2f v) {
	return sf::Vector2f(v.x, windowHeight - v.y);
}

sf::Vector2f conv(float x, float y) {
	return sf::Vector2f(x, windowHeight - y);
}


sf::Vector2f calcCorner(sf::Vector2f old, sf::Vector2f c, float theta) {

	float z = sqrt(pow(c.x - old.x, 2) + pow(c.y - old.y, 2));

	
	sf::Vector2f v = sf::Vector2f(c.x + z * sin(theta * (3.1415926 / 180.0f)), c.y + z * cos(theta * (3.1415926 / 180.0f)));
	std::cout << c.x << " " << c.y << std::endl;
	std::cout << v.x << " " << v.y << std::endl;
	return v;
}
