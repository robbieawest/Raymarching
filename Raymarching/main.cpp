
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

	Point test1 = Point(sf::Vector2f(0.0f, 0.0f), 5);
	Point test2 = Point(sf::Vector2f(0.0f, 0.0f), 5);

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
				else if (evnt.text.unicode == 'r') {
					rayMarch(dir, p.pos, circles, squares, test1, test2);
				}
				break;
			}
		}
		sf::Vector2i mP = sf::Mouse::getPosition(window);
		if (movingP) {
			p.move(sf::Vector2f(float(mP.x), float(mP.y)));
		}
		else {

			//calculate angle for raymarch
			sf::Vector2f v = conv(sf::Vector2f(float(mP.x), float(mP.y))) - conv(p.pos);

			if (v.x > 0 && v.y > 0){
				dir = atan(v.x / v.y) * 180.0f / 3.1415926f;
			}
			else if (v.x > 0 && v.y < 0) {

				dir = atan(v.y / v.x) * 180.0f / 3.1415926f;
				dir = dir < 0 ? dir *= -1 : dir;
				dir += 90;
			}
			else if (v.x < 0 && v.y < 0) {
				dir = atan(v.x / v.y) * 180.0f / 3.1415926f;
				dir += 180.0f;
			}
			else if (v.x < 0 && v.y > 0) {
				dir = atan(v.y / v.x) * 180.0f / 3.1415926f;
				dir = dir < 0 ? dir *= -1 : dir;
				dir += 270.0f;
			}

		}



		window.clear();

		for (auto& x : squares)x.draw(window);
		for (auto& x : circles)x.draw(window);

		window.draw(p.rep);

		window.draw(test1.rep);
		window.draw(test2.rep);

		window.display();
	}

	return 0;
}