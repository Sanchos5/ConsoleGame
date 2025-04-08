#pragma once

namespace sf
{
	class Sprite;
}

struct Vector2D
{
	float X = 0.0f;
	float Y = 0.0f;
};

typedef Vector2D Position2D;

Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);

bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
	Position2D rect2Position, Vector2D rect2Size);

bool IsCirclesCollide(Position2D circle1Position, float circle1Radius,
	Position2D circle2Position, float circle2Radius);

void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);