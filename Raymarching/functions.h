#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point.h"
#include "rectUse.h"
#include "circleUse.h"
#include "line.h"





sf::Vector2f conv(sf::Vector2f v);
sf::Vector2f conv(float x, float y);
sf::Vector2f calcCorner(sf::Vector2f old, sf::Vector2f c, float theta, int type);
void vCout(sf::Vector2f v, std::string t);
void rayMarch(float d, sf::Vector2f p, std::vector<circleUse>& c, std::vector<rectUse>& r);

