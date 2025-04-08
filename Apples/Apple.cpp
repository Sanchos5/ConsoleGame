
#include "Apple.h"

void InitApple(Apple& apple)
{
	apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	apple.shape.setRadius(APPLE_SIZE / 2.0f);
	apple.shape.setFillColor(sf::Color::Red);
	apple.shape.setOrigin(APPLE_SIZE / 2.0f, APPLE_SIZE / 2.0f);
	apple.shape.setPosition(apple.position.X, apple.position.Y);
}