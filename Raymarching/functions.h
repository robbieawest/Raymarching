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


sf::Vector2f calcCorner(sf::Vector2f old, sf::Vector2f c, float theta, int type) {

	
	float z = sqrt(pow(c.x - old.x, 2) + pow(c.y - old.y, 2));

//	std::cout << theta << std::endl;

	switch (type) {
	case 1:
		//top left
		theta += 315.0f;
		break;
	case 2:
		//top right
		theta += 45.0f;
		break;

	case 3:
		//bottom right
		theta += 135.0f;
		break;
	case 4:
		//bottom left
		theta += 225.0f;
		break;
	}

	//std::cout << "Theta: " << theta << std::endl;
//	std::cout << "Z: " << z << std::endl;


	
	sf::Vector2f v = sf::Vector2f(c.x + z * sin(theta * (3.1415926f / 180.0f)), c.y + z * cos(theta * (3.1415926f / 180.0f)));
//	std::cout << "Center: " << c.x << " " << c.y << std::endl;
//	std::cout << "Result: " << v.x << " " << v.y << std::endl;
//	std::cout << "------------------------" << std::endl;
	return v;
}

void vCout(sf::Vector2f v, std::string t) {
	if(t.size() > 0)
		std::cout << t << ": " << v.x << " " << v.y << std::endl;
	else {
		std::cout << v.x << " " << v.y << std::endl;
	}
}
