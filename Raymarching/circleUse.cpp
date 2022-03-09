#include "functions.h"

circleUse::circleUse(float r, sf::Vector2f pos, sf::Color col, int opacity) {

	self.setRadius(r);
	self.setOrigin(r, r);
	self.setPosition(conv(pos));
	self.setFillColor(sf::Color(0, 0, 0, opacity));
	self.setOutlineColor(col);
	self.setOutlineThickness(1);

//	p1 = Point(pos, 5);
//	p2 = Point(sf::Vector2f(pos.x + r, pos.y), 5);
//	p3 = Point(sf::Vector2f(pos.x - r, pos.y), 5);
}

void circleUse::draw(sf::RenderWindow& window) {
	window.draw(self);

//	window.draw(p1.rep);
//	window.draw(p2.rep);
//	window.draw(p3.rep);
}
