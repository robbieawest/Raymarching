#include "functions.h"

circleUse::circleUse(float r, sf::Vector2f pos, sf::Color col) {
	self.setRadius(r);
	self.setOrigin(r / 2.0f, r / 2.0f);
	self.setPosition(conv(pos));
	self.setFillColor(sf::Color::Black);
	self.setOutlineColor(col);
	self.setOutlineThickness(-5);
}

void circleUse::draw(sf::RenderWindow& window) {
	window.draw(self);
}
