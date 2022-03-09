
#pragma once
#include "functions.h"

sf::Vector2f conv(sf::Vector2f v) {
	return sf::Vector2f(v.x, 800 - v.y);
}

sf::Vector2f conv(float x, float y) {
	return sf::Vector2f(x, 800 - y);
}

float pythag(sf::Vector2f v) {

	return sqrt(v.x * v.x + v.y * v.y);
}

float MAX(float a, float b) {
	return a > b ? a : b;
}

float MIN(float a, float b) {
	return a < b ? a : b;
}

bool outOfBounds(sf::Vector2f v) {
	return v.x < 0.0f || v.y < 0.0f || v.x > 1200.0f || v.y > 800.0f;
}

sf::Vector2f calcCorner(sf::Vector2f old, sf::Vector2f c, float theta, int type) {

	float z = pythag(c - old);
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


float distanceToLineSegment(line l, sf::Vector2f p) {
	//get mathematical representation, get perpendicular grad and set it to new line intersecting p, get intersect of two lines and check if inside range of segment
	//if this is true^, then get distance from intersect
	//if false then return 1000000

	float perpGrad = l.returnPerpGrad();

	line perpLine(perpGrad, perpGrad * -1 * p.x + p.y);
	sf::Vector2f intersect = l.returnIntersect(perpLine, l.p1, perpLine.p1);

	if (l.checkInSmallLine(intersect, l.p1)) {
		return pythag(intersect - p);
	}
	else {
		return 1000000.0f;
	}
}

float returnDistToR(rectUse& r, sf::Vector2f p) {
	std::vector<float> potentialDistances;

	std::vector<sf::Vector2f> corners;
	corners.push_back(conv(r.p1.pos));
	corners.push_back(conv(r.p2.pos));
	corners.push_back(conv(r.p3.pos));
	corners.push_back(conv(r.p4.pos));


	potentialDistances.push_back(pythag(p - corners[0]));
	potentialDistances.push_back(pythag(p - corners[1]));
	potentialDistances.push_back(pythag(p - corners[2]));
	potentialDistances.push_back(pythag(p - corners[3]));

	potentialDistances.push_back(distanceToLineSegment(line(corners[1], corners[0]), p));
	potentialDistances.push_back(distanceToLineSegment(line(corners[2], corners[1]), p));
	potentialDistances.push_back(distanceToLineSegment(line(corners[3], corners[2]), p));
	potentialDistances.push_back(distanceToLineSegment(line(corners[0], corners[3]), p));

	float fReturn = potentialDistances[0];
	
	for (auto& x : potentialDistances) fReturn = x < fReturn ? x : fReturn;
	return fReturn;
}

float returnDistToC(circleUse c, sf::Vector2f p) {
	return pythag(p - conv(c.self.getPosition())) - c.self.getRadius();
}

void rayMarch(float d, sf::Vector2f p, std::vector<circleUse>& c, std::vector<rectUse>& r, circleUse& tc, std::vector<circleUse> &radii, std::vector<sf::RectangleShape> &collisions, sf::RectangleShape &line) {

	sf::Vector2f convP = conv(p);

	//Main function
	
	//find closest distance between point and any shape
	//draw circle with the distance as the radius
	//move along ray line for the distance: radius
	//keep going until the distance moved is very very small
	//project and display this

	//^This or it goes out of bounds

	float closestDistance = 1000000.0f; //very high so anything would be closer

	sf::Vector2f currentPos = convP;
	radii.clear();

	//Deal with direction
	//This allows computer to view calculations with an acute angle, but still take the non-acute picture into account
	//just store values on sign of vector based on angle
	sf::Vector2f dirComplement(1.0f, 1.0f);

	if (d <= 90.0f) {
		d = 90.0f - d;
	}
	else if (d <= 180.0f) {
		dirComplement.y *= -1.0f;
		d -= 90.0f;
	}
	else if (d <= 270.0f) {
		dirComplement.x *= -1.0f; dirComplement.y *= -1.0f;
		d -= 180.0f;
		d = 90.0f - d;
	}
	else if (d <= 360.0f) {
		dirComplement.x *= -1;
		d -= 270.0f;
	}



	while (closestDistance > 1 && !outOfBounds(conv(currentPos))) {
		//Advance

		//Find closest
		//Circles
		closestDistance = 100000.0f;
		for (auto& x : c) {
			float d = returnDistToC(x, currentPos);
			closestDistance = MIN(d, closestDistance);
		}
		//Rects
		for (auto &x : r) {
			float d = returnDistToR(x, currentPos);
			closestDistance = MIN(d, closestDistance);
		}


		radii.push_back(circleUse(closestDistance, currentPos, sf::Color(100, 100, 100)));

		//Update Position

		sf::Vector2f addV = sf::Vector2f(closestDistance * cos(d * 3.1415926f / 180.0f), closestDistance * sin(d * 3.1415926f / 180.0f));
		addV.x *= dirComplement.x;
		addV.y *= dirComplement.y;
		currentPos += addV;



	}

//	std::cout << "Raymarch ended at " << currentPos.x << " " << currentPos.y << std::endl;
	if (closestDistance < 1) {
		sf::RectangleShape temp(sf::Vector2f(1, 1));
		temp.setPosition(conv(currentPos));

	//	std::cout << "Collision placed and occured at " << currentPos.x << " " << currentPos.y << std::endl;
		collisions.push_back(temp);
	}

	//Line
}


bool IN_RANGE(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {	

	return c.x <= MAX(a.x, b.x)
		&& c.x >= MIN(a.x, b.x)

		&& c.y <= MAX(a.y, b.y)
		&& c.y >= MIN(a.y, b.y);
}
