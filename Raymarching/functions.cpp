
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

sf::Vector2f closestPointC(circleUse C, sf::Vector2f point) {
	sf::Vector2f fullD = conv(C.self.getPosition()) - conv(point);
	vCout(conv(C.self.getPosition()), "Circle");
	vCout(conv(point), "Point");
	vCout(fullD, "Diff");
	float theta = atan(fullD.y / fullD.x);
	std::cout << theta * 180.0f / 3.1415926f << std::endl;

	sf::Vector2f take = sf::Vector2f(C.self.getRadius() * cos(theta), C.self.getRadius() * sin(theta));
	if ((fullD.x < 0 && take.x >= 0) || (fullD.x >= 0 && take.x < 0))take.x *= -1;
	if ((fullD.y < 0 && take.y >= 0) || (fullD.y >= 0 && take.x < 0))take.y *= -1;

	vCout(take, "Take");

	sf::Vector2f v = fullD - take;
	vCout(v, "End");
	std::cout << "----------------" << std::endl;
	return conv(point) + v;
	
}

void rayMarch(float d, sf::Vector2f p, std::vector<circleUse> &c, std::vector<rectUse> &r, Point &t1, Point &t2) {

	//Main function
	
	//find closest point between all of squares / circles
	//draw circle with the distance as the radius
	//move along ray line for the distance: radius
	//keep going until the distance moved is very very small
	//project and display this

	t1.move(conv(closestPointC(c[0], p)));
	t2.move(conv(closestPointC(c[1], p)));


}
