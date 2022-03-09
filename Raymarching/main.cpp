
#include "functions.h"


int main() {
	int windowWidth = 1200;
	int windowHeight = 800;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Raymarching", sf::Style::Default);

	Point p = Point(sf::Vector2f(200, 300), 10);

	std::vector<rectUse> squares;
	std::vector<circleUse> circles;

	squares.push_back(rectUse(sf::Vector2f(100, 100), sf::Vector2f(500, 500), 30, sf::Color(0, 0, 0))); //Only squares
	squares.push_back(rectUse(sf::Vector2f(250, 250), sf::Vector2f(200, 200), 50, sf::Color(0, 0, 0)));

	circles.push_back(circleUse(100, sf::Vector2f(700, 400), sf::Color(0, 0, 0), 255));
	circles.push_back(circleUse(50, sf::Vector2f(900, 200), sf::Color(0, 0, 0), 255));


	bool movingP = true;
	bool mouseRay = false;

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
	//
	sf::Text fps;
	fps.setCharacterSize(25.0f);
	fps.setString("");
	fps.setFillColor(sf::Color(255, 0, 0, 200));
	fps.setFont(calibri);

	//Delta Time
	sf::Clock deltaClock;
	float deltaTime;

	std::cout << "Raymarching algorithm visualisation(Sphere tracing)\nKeybinds:\n";
	std::cout << "'p' display points on rects\n";
	std::cout << "'m' start raymarching towards mouse position\n";
	std::cout << "'s' start raymarching automatically in a circle\n";
	std::cout << "'c' clear collisions" << std::endl;
	
	while (window.isOpen()) {
		sf::Event evnt;

		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode == 'p') {
					//Draw points on squares
					for (auto& x : squares)x.drawingCorners = !x.drawingCorners;
				}
				else if (evnt.text.unicode == 'm') {
					//Stop point moving and start raymarching towards mouse position
					movingP = !movingP;
					mouseRay = !mouseRay;
				}
				else if (evnt.text.unicode == 's') {
					//Start/Stop spinng
					if (!mouseRay && !movingP) {
						movingP = !movingP;
					}
					else {
						movingP = false;
						mouseRay = false;
					}
				}
				else if (evnt.text.unicode == 'c') {
					collisions.clear();
				}
				break;
			}
		}

		sf::Vector2i mP = sf::Mouse::getPosition(window);
		deltaTime = 1.0f / deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		if (movingP) {
			p.move(sf::Vector2f(float(mP.x), float(mP.y)));
		}
		else if(mouseRay){

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

			rayMarch(dir, p.pos, circles, squares, radii, collisions, line);
		}
		else {
			dir = dir >= 360.0f ? 0.0f : dir + 30.0f / deltaTime;
			rayMarch(dir, p.pos, circles, squares, radii, collisions, line);
		}

		fps.setString(std::to_string(deltaTime));

		//Clear back buffer
		window.clear(sf::Color(30, 30, 30));

		//Draw to back buffer

		//Draw shapes
		for (auto& x : squares)x.draw(window);
		for (auto& x : circles)x.draw(window);

		//Point
		window.draw(p.rep);

		//Displays for algorithm

		for (auto& x : radii)x.draw(window);
		for (auto& x : collisions)window.draw(x);
		window.draw(line);

		//FPS
		window.draw(fps);
		
		//Swap back buffer and front buffer
		window.display();
	}

	return 0;
}