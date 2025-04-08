
#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
{
	Position2D result;
	result.X = rand() / (float)RAND_MAX * screenWidth;
	result.Y = rand() / (float)RAND_MAX * screenHeight;
	return result;
}

bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
	Position2D rect2Position, Vector2D rect2Size)
{
	float dx = (float)fabs(rect1Position.X - rect2Position.X);
	float dy = (float)fabs(rect1Position.Y - rect2Position.Y);

	return (dx <= (rect1Size.X + rect2Size.X) / 2.0f &&
		dy <= (rect1Size.Y + rect2Size.Y) / 2.0f);
}

bool IsCirclesCollide(Position2D circle1Position, float circle1Radius,
	Position2D circle2Position, float circle2Radius)
{
	float squareDistance = (circle1Position.X - circle2Position.X) * (circle1Position.X - circle2Position.X) +
		(circle1Position.Y - circle2Position.Y) * (circle1Position.Y - circle2Position.Y);
	float squareRadisuSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius) / 4;

	return squareDistance <= squareRadisuSum;
}

void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
{
	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sf::Vector2f scale = { desiredWidth / spriteRect.width,  desiredHeight / spriteRect.height };
	sprite.setScale(scale);
}

void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
{
	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
}
