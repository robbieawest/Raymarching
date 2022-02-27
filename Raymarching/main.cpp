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

	sf::Vector2f p1;
	sf::Vector2f p2;
	float grad;
	float yInte;

	line(sf::Vector2f p, sf::Vector2f P) {
		p1 = p;
		p2 = P;

		grad = (p1.y - p2.y) / (p1.x - p2.x);
		yInte = 0;
		//get this next
	}

	float returnPerpGrad() {
		return -1 * (1 / grad);
	}

	bool checkInLine(sf::Vector2f p) {
		return p.y == p.x * grad + yInte;
	}
};


class rectUse {
public:
	sf::RectangleShape self;
	Point p1;
	Point p2;
	Point p3;
	Point p4;
	Point p5;

	bool drawingCorners;

	rectUse(sf::Vector2f size, sf::Vector2f pos, float rot, sf::Color oCol) {

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

		p1.move(conv(calcCorner(topLeftOld, center, rot, 4)));
		p1.rep.setRadius(10);
		p1.rep.setFillColor(sf::Color::Red);
		p1.rep.setOrigin(5, 5);


		p2.move(conv(calcCorner(topRightOld, center, rot, 1)));
		p2.rep.setRadius(10);
		p2.rep.setOrigin(5, 5);
		p2.rep.setFillColor(sf::Color::Blue);

		p3.move(conv(calcCorner(bottomLeftOld, center, rot, 2)));
		p3.rep.setOrigin(5, 5);
		p3.rep.setRadius(10);
		p3.rep.setFillColor(sf::Color::Green);
			
		p4.move(conv(calcCorner(bottomRightOld, center, rot, 3)));
		p4.rep.setRadius(10);
		p4.rep.setOrigin(5, 5);
		p4.rep.setFillColor(sf::Color::Magenta);

		p5.move(conv(center.x, center.y));
		p5.rep.setRadius(10);
		p5.rep.setOrigin(5, 5);
		p5.rep.setFillColor(sf::Color::Blue);
	}

	void outputBounds() {
		
		std::cout << self.getGlobalBounds().left << " " << self.getGlobalBounds().top << " " << self.getGlobalBounds().width << " " << self.getGlobalBounds().height << std::endl;
	}

	void draw(sf::RenderWindow& window) {
		window.draw(self);

		if (drawingCorners) {
			window.draw(p1.rep);
			window.draw(p2.rep);
			window.draw(p3.rep);
			window.draw(p4.rep);
			window.draw(p5.rep);
		}
	}
};


int main() {

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Raymarching", sf::Style::Default);

	Point p = Point(sf::Vector2f(200, 300), 10);

	std::vector<rectUse> squares;

	rectUse square = rectUse(sf::Vector2f(100, 100), sf::Vector2f(500, 500), 20, sf::Color::Red); //Only squares pls

	squares.push_back(square);

	
	while (window.isOpen()) {
		sf::Event evnt;

		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				if(evnt.text.unicode == 'a')
					std::cout << conv(p.pos.x, p.pos.y).x << " " << conv(p.pos.x, p.pos.y).y << std::endl;
				else if (evnt.text.unicode == 'p') {
					for (auto& x : squares)x.drawingCorners = !x.drawingCorners;
				}
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