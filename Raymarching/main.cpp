
#include "functions.h"


int main() {
	int windowWidth = 1200;
	int windowHeight = 800;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Raymarching", sf::Style::Default);

	Point p = Point(sf::Vector2f(200, 300), 10);

	std::vector<rectUse> squares;
	std::vector<circleUse> circles;

	squares.push_back(rectUse(sf::Vector2f(100, 100), sf::Vector2f(500, 500), 30, sf::Color::Red)); //Only squares
	squares.push_back(rectUse(sf::Vector2f(250, 250), sf::Vector2f(200, 200), 50, sf::Color::Yellow));

	circles.push_back(circleUse(100, sf::Vector2f(700, 400), sf::Color::Blue));
	circles.push_back(circleUse(50, sf::Vector2f(900, 200), sf::Color::Magenta));

	circleUse testCircle(0.0f, sf::Vector2f(0.0f, 0.0f), sf::Color(200, 200, 200));

	bool movingP = true;
	float dir = -1.0f;

	//Items for displaying
	std::vector<circleUse> radii;
	std::vector<sf::RectangleShape> collisions;
	sf::RectangleShape line;
	line.setFillColor(sf::Color::White);

	//FPS counter
	//Font
	sf::Font calibri;
	if (!calibri.loadFromFile("calibri.ttf")) {
		std::cout << "Error loading calibri font" << std::endl;
	}
	sf::Text fps;
	fps.setCharacterSize(25.0f);
	fps.setString("");
	fps.setFillColor(sf::Color(255, 0, 0, 200));
	fps.setFont(calibri);

	
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
					rayMarch(dir, p.pos, circles, squares, testCircle, radii, collisions, line);
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

		//	rayMarch(dir, p.pos, circles, squares, testCircle, radii, collisions, line);
		}

	//	testCircle.self.setPosition(sf::Vector2f(float(mP.x), float(mP.y)));



		window.clear();

	//	testCircle.draw(window);

		for (auto& x : squares)x.draw(window);
		for (auto& x : circles)x.draw(window);

		window.draw(p.rep);

		//Displays for algorithm

		for (auto& x : radii)x.draw(window);
		for (auto& x : collisions)window.draw(x);
		window.draw(line);
		
		window.display();
	}

	return 0;
}