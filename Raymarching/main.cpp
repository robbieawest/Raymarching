
#include "functions.h"
#include <cmath>







int main() {
	int windowWidth = 1200;
	int windowHeight = 800;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Raymarching", sf::Style::Default);

	Point p = Point(sf::Vector2f(200, 300), 10);

	std::vector<rectUse> squares;
	std::vector<circleUse> circles;

	squares.push_back(rectUse(sf::Vector2f(100, 100), sf::Vector2f(500, 500), 20, sf::Color::Red)); //Only squares
	squares.push_back(rectUse(sf::Vector2f(50, 50), sf::Vector2f(200, 200), 40, sf::Color::Yellow));

	circles.push_back(circleUse(50, sf::Vector2f(25, 250), sf::Color::Blue));
	circles.push_back(circleUse(20, sf::Vector2f(900, 200), sf::Color::Magenta));

	bool movingP = true;
	float dir = -1.0f;

	
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
				else if (evnt.text.unicode == 'm') {
					movingP = !movingP;
				}
				break;
			}
		}
		sf::Vector2i mP = sf::Mouse::getPosition(window);
		if (movingP) {
			p.move(sf::Vector2f(float(mP.x), float(mP.y)));
		}
		else {
			sf::Vector2f v = conv(sf::Vector2f(float(mP.x), float(mP.y))) - p.pos;
			dir = atan(v.y / v.x) * 180.0f / 3.1415926f;

			//change here
			std::cout << dir << std::endl;
		}

		rayMarch(dir, p.pos, circles, squares);


		window.clear();

		for (auto& x : squares)x.draw(window);
		for (auto& x : circles)x.draw(window);

		window.draw(p.rep);

		window.display();
	}

	return 0;
}