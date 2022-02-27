
#pragma once
#include "functions.h"

sf::Vector2f conv(sf::Vector2f v) {
	return sf::Vector2f(v.x, 800 - v.y);
}

sf::Vector2f conv(float x, float y) {
	return sf::Vector2f(x, 800 - y);
}


sf::Vector2f calcCorner(sf::Vector2f old, sf::Vector2f c, float theta, int type) {

	
	float z = sqrt(pow(c.x - old.x, 2) + pow(c.y - old.y, 2));
	theta += 45.0f + 90.0f * (type - 1);

	return sf::Vector2f(c.x + z * sin(theta * (3.1415926f / 180.0f)), c.y + z * cos(theta * (3.1415926f / 180.0f)));
}

void vCout(sf::Vector2f v, std::string t) {
	if(t.size() > 0)
		std::cout << t << ": " << v.x << " " << v.y << std::endl;
	else {
		std::cout << v.x << " " << v.y << std::endl;
	}
}

void rayMarch(float d, sf::Vector2f p, std::vector<circleUse> &c, std::vector<rectUse> &r) {

	//Main function
	
	//find closest point between all of squares / circles
	//draw circle with the distance as the radius
	//move along ray line for the distance: radius
	//keep going until the distance moved is very very small
	//project and display this


}
