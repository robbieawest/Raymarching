#include "functions.h"

rectUse::rectUse(float width, sf::Vector2f pos, float rot, sf::Color oCol) {

	sf::Vector2f size(width, width);

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

	corners.push_back(calcCorner(topRightOld, center, rot, 1));
	corners.push_back(calcCorner(bottomRightOld, center, rot, 2));
	corners.push_back(calcCorner(bottomLeftOld, center, rot, 3));
	corners.push_back(calcCorner(topLeftOld, center, rot, 4));


	rotation = rot;
	
}

void rectUse::outputBounds() {
	
	std::cout << self.getGlobalBounds().left << " " << self.getGlobalBounds().top << " " << self.getGlobalBounds().width << " " << self.getGlobalBounds().height << std::endl;
}

void rectUse::draw(sf::RenderWindow& window) {
	window.draw(self);
}
