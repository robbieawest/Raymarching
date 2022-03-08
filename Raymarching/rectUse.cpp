#include "functions.h"

rectUse::rectUse(sf::Vector2f size, sf::Vector2f pos, float rot, sf::Color oCol) {

	drawingCorners = false;

	self.setSize(size);
	self.setOrigin(size.x / 2, size.y / 2);
	self.setPosition(conv(pos));
	self.setFillColor(sf::Color::Black);
	self.setOutlineColor(oCol);
	self.setOutlineThickness(-3.0f); 
	self.setRotation(rot);

	//Get corners using math
	sf::Vector2f oldpos = sf::Vector2f(pos.x - size.x / 2, pos.y + size.y / 2);


	sf::Vector2f topLeftOld = oldpos;
	sf::Vector2f topRightOld = sf::Vector2f(oldpos.x + size.x, oldpos.y);
	sf::Vector2f bottomLeftOld = sf::Vector2f(oldpos.x, oldpos.y - size.y);
	sf::Vector2f bottomRightOld = sf::Vector2f(oldpos.x + size.x, oldpos.y - size.y);

	//Come back here later, there is a wierd offset which i think is just attributed to the wierd outlines and origins, and not to my math

	sf::Vector2f center = sf::Vector2f(oldpos.x + size.x / 2, oldpos.y - size.y / 2);

	p4.move(conv(calcCorner(topLeftOld, center, rot, 4)));
	p4.rep.setRadius(10);
	p4.rep.setFillColor(sf::Color::Red);
	p4.rep.setOrigin(10, 10);


	p1.move(conv(calcCorner(topRightOld, center, rot, 1)));
	p1.rep.setRadius(10);
	p1.rep.setOrigin(10, 10);
	p1.rep.setFillColor(sf::Color::Blue);

	p2.move(conv(calcCorner(bottomLeftOld, center, rot, 2)));
	p2.rep.setOrigin(10, 10);
	p2.rep.setRadius(10);
	p2.rep.setFillColor(sf::Color::Green);
		
	p3.move(conv(calcCorner(bottomRightOld, center, rot, 3)));
	p3.rep.setRadius(10);
	p3.rep.setOrigin(10, 10);
	p3.rep.setFillColor(sf::Color::Magenta);

	p5.move(conv(center.x, center.y));
	p5.rep.setRadius(10);
	p5.rep.setOrigin(10, 10);
	p5.rep.setFillColor(sf::Color::Blue);

	rotation = rot;
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
