#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int windowWidth = 1200;
int windowHeight = 800;

sf::Vector2f conv(sf::Vector2f v) {
	return sf::Vector2f(v.x, windowHeight - v.y);
}

sf::Vector2f conv(float x, float y) {
	return sf::Vector2f(x, windowHeight - y);
}


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

sf::Vector2f calcCorner(sf::Vector2f old, sf::Vector2f c, float theta) {

	sf::Vector2f r = sf::Vector2f(0.0f, 0.0f);
	float z = sqrt(pow(old.x - c.x, 2) + (old.y - c.y, 2));
	float z1 = z * cos(theta);
	
	for (int i = 0; i < 20; i++) {
		r.x = z1 + c.x + c.y - r.y;
		r.y = z1 + c.x + c.y - r.x;
	}

	return r;	
}

class rectUse {
public:
	sf::RectangleShape self;
	Point p1;
	Point p2;
	Point p3;
	Point p4;

	rectUse(sf::Vector2f size, sf::Vector2f pos, float rot, sf::Color oCol) {
		sf::Vector2f oldpos = pos;
		self.setSize(size);
		self.setOrigin(size.x / 2, size.y / 2);
		self.setPosition(conv(pos));
		self.setFillColor(sf::Color::Black);
		self.setOutlineColor(oCol);
		self.setOutlineThickness(-3.0f); 
		self.setRotation(rot);

		//Get corners using mathhh
		sf::Vector2f topLeftOld = oldpos;
		sf::Vector2f topRightOld = sf::Vector2f(oldpos.x + size.x, oldpos.y);
		sf::Vector2f bottomLeftOld = sf::Vector2f(oldpos.x, oldpos.y + size.y);
		sf::Vector2f bottomRightOld = oldpos + size;

		sf::Vector2f center = sf::Vector2f(oldpos.x + size.x / 2, oldpos.y + size.y / 2);

		p1.move(calcCorner(topLeftOld, center, rot));
		p1.rep.setRadius(10);
		p1.rep.setFillColor(sf::Color::Red);

			
	}

	void outputBounds() {
		
		std::cout << self.getGlobalBounds().left << " " << self.getGlobalBounds().top << " " << self.getGlobalBounds().width << " " << self.getGlobalBounds().height << std::endl;
	}

	void draw(sf::RenderWindow& window) {
		window.draw(self);
		window.draw(p1.rep);
	}
};


int main() {

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Raymarching", sf::Style::Default);

	Point p = Point(sf::Vector2f(200, 300), 10);

	std::vector<rectUse> squares;

	rectUse square = rectUse(sf::Vector2f(100, 100), sf::Vector2f(500, 500), 30, sf::Color::Red);
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