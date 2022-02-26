#include <SFML/Graphics.hpp>
#include <iostream>
#include "functions.h"
#include <cmath>



class Point {
public:

	sf::CircleShape rep;
	sf::Vector2f pos;


	Point(sf::Vector2f p, float r) {

		rep.setRadius(r);
		rep.setOrigin(sf::Vector2f(r / 2.0f, r / 2.0f));
		rep.setFillColor(sf::Color::Green);
		rep.setPosition(conv(p));

		pos = p;
	}

	Point() {
		rep.setRadius(0);
		pos = sf::Vector2f();
	}

	void move(sf::Vector2f p) {
		pos = p;
		rep.setPosition(pos);
	}

};

class line {
public:

	float grad;
	float yInte;

	line(float m, float c) {
		grad = m;
		yInte = c;
	}

	float returnPerpGrad() {
		return -1 * (1 / grad);
	}
};


class rectUse {
public:
	sf::RectangleShape self;
	Point p1;
	Point p2;
	Point p3;
	Point p4;

	rectUse(sf::Vector2f size, sf::Vector2f pos, float rot, sf::Color oCol) {


		sf::Vector2f oldpos = sf::Vector2f(pos.x - size.x / 2, pos.y + size.y / 2);

		self.setSize(size);
		self.setOrigin(size.x / 2, size.y / 2);
		self.setPosition(conv(pos));
		self.setFillColor(sf::Color::Black);
		self.setOutlineColor(oCol);
		self.setOutlineThickness(-3.0f); 
		self.setRotation(rot);

		//Get corners using math
		sf::Vector2f topLeftOld = sf::Vector2f(pos.x - size.x / 2, pos.y + size.y / 2);
		sf::Vector2f topRightOld = sf::Vector2f(oldpos.x + size.x, oldpos.y);
		sf::Vector2f bottomLeftOld = sf::Vector2f(oldpos.x, oldpos.y - size.y);
		sf::Vector2f bottomRightOld = sf::Vector2f(oldpos.x + size.x, oldpos.y - size.y);

		sf::Vector2f center = sf::Vector2f(oldpos.x + size.x / 2, oldpos.y - size.y / 2);

		p1.move(conv(calcCorner(topLeftOld, center, rot)));
		p1.rep.setRadius(10);
		p1.rep.setFillColor(sf::Color::Red);
		p1.rep.setOrigin(5, 5);

		std::cout << p1.pos.x << " " << p1.pos.y << std::endl;

		p2.move(conv(topLeftOld));
		p2.rep.setOrigin(5, 5);
		p2.rep.setRadius(10);
		p2.rep.setFillColor(sf::Color::Green);

		p3.move(conv(topRightOld));
		p3.rep.setOrigin(5, 5);
		p3.rep.setRadius(10);
		p3.rep.setFillColor(sf::Color::Green);
			
		p4.move(conv(bottomLeftOld));
		p4.rep.setOrigin(5, 5);
		p4.rep.setRadius(10);
		p4.rep.setFillColor(sf::Color::Green);
	}

	void outputBounds() {
		
		std::cout << self.getGlobalBounds().left << " " << self.getGlobalBounds().top << " " << self.getGlobalBounds().width << " " << self.getGlobalBounds().height << std::endl;
	}

	void draw(sf::RenderWindow& window) {
		window.draw(self);
		window.draw(p1.rep);
		window.draw(p2.rep);
		window.draw(p3.rep);
		window.draw(p4.rep);
	}
};


int main() {

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Raymarching", sf::Style::Default);

	Point p = Point(sf::Vector2f(200, 300), 10);

	std::vector<rectUse> squares;

	rectUse square = rectUse(sf::Vector2f(100, 100), sf::Vector2f(500, 500), 0, sf::Color::Red);
//	rectUse square1 = rectUse(sf::Vector2f(100, 100), sf::Vector2f(500, 500), 0, sf::Color::Green);

//	squares.push_back(square1);
	squares.push_back(square);
	
	while (window.isOpen()) {
		sf::Event evnt;

		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				std::cout << p.pos.x << " " << p.pos.y << std::endl;
				break;
			}
		}
		sf::Vector2i mP = sf::Mouse::getPosition(window);
		p.move(sf::Vector2f(float(mP.x), float(mP.y)));


		window.clear();

		for (auto& x : squares)x.draw(window);

		window.draw(p.rep);

		window.display();
	}

	return 0;
}