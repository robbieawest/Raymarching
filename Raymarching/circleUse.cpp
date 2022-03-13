#include "functions.h"

circleUse::circleUse(float r, sf::Vector2f pos, sf::Color col, int opacity) {

	self.setRadius(r);
	self.setOrigin(r, r);
	self.setPosition(conv(pos));
	self.setFillColor(sf::Color(0, 0, 0, opacity));
	self.setOutlineColor(col);
	self.setOutlineThickness(1);

}

void circleUse::draw(sf::RenderWindow& window) {
	window.draw(self);
}
