#pragma once

#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

struct Rock
{
	Position2D position;
	sf::RectangleShape shape;
};

void InitRock(Rock& rock);