#pragma once

#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

struct Apple
{
	Position2D position;
	sf::CircleShape shape;
};

void InitApple(Apple& apple);
