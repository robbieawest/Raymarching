#include "functions.h"

rectUse::rectUse(sf::Vector2f size, sf::Vector2f pos, float rot, sf::Color oCol) {

	drawingCorners = false;

	self.setSize(size);
	self.setOrigin(size.x / 2, size.y / 2);
	self.setPosition(conv(pos));
	self.setFillColor(sf::Color(0, 0, 0));
	self.setOutlineColor(oCol);
	self.setOutlineThickness(1); 
	self.setRotation(rot);

	//Get corners using math
	sf::Vector2f oldpos = sf::Vector2f(pos.x - size.x / 2, pos.y + size.y / 2);


	sf::Vector2f topLeftOld = oldpos;
	sf::Vector2f topRightOld = sf::Vector2f(oldpos.x + size.x, oldpos.y);
	sf::Vector2f bottomLeftOld = sf::Vector2f(oldpos.x, oldpos.y - size.y);
	sf::Vector2f bottomRightOld = sf::Vector2f(oldpos.x + size.x, oldpos.y - size.y);

	//Come back here later, there is a wierd offset which i think is just attributed to the wierd outlines and origins, and not to my math

	sf::Vector2f center = sf::Vector2f(oldpos.x + size.x / 2, oldpos.y - size.y / 2);

	float pointRadius = 4.0f;
	p4.move(conv(calcCorner(topLeftOld, center, rot, 4)));
	p4.rep.setRadius(pointRadius);
	p4.rep.setFillColor(sf::Color::Red);
	p4.rep.setOrigin(pointRadius, pointRadius);


	p1.move(conv(calcCorner(topRightOld, center, rot, 1)));
	p1.rep.setRadius(pointRadius);
	p1.rep.setOrigin(pointRadius, pointRadius);
	p1.rep.setFillColor(sf::Color::Blue);

	p2.move(conv(calcCorner(bottomLeftOld, center, rot, 2)));
	p2.rep.setOrigin(pointRadius, pointRadius);
	p2.rep.setRadius(pointRadius);
	p2.rep.setFillColor(sf::Color::Green);
		
	p3.move(conv(calcCorner(bottomRightOld, center, rot, 3)));
	p3.rep.setRadius(pointRadius);
	p3.rep.setOrigin(pointRadius, pointRadius);
	p3.rep.setFillColor(sf::Color::Magenta);

	p5.move(conv(center.x, center.y));
	p5.rep.setRadius(pointRadius);
	p5.rep.setOrigin(pointRadius, pointRadius);
	p5.rep.setFillColor(sf::Color::Blue);

	rotation = rot;
	nonRotatedCorners.push_back(conv(calcCorner(topRightOld, center, 0.0f, 1)));
	nonRotatedCorners.push_back(conv(calcCorner(bottomRightOld, center, 0.0f, 2)));
	nonRotatedCorners.push_back(conv(calcCorner(bottomLeftOld, center, 0.0f, 3)));
	nonRotatedCorners.push_back(conv(calcCorner(topLeftOld, center, 0.0f, 4)));
	
}

void rectUse::outputBounds() {
	
	std::cout << self.getGlobalBounds().left << " " << self.getGlobalBounds().top << " " << self.getGlobalBounds().width << " " << self.getGlobalBounds().height << std::endl;
}

void rectUse::draw(sf::RenderWindow& window) {
	window.draw(self);

	if (drawingCorners) {
		window.draw(p1.rep);
		window.draw(p2.rep);
		window.draw(p3.rep);
		window.draw(p4.rep);
		window.draw(p5.rep);
	}
}
