
#include "Rock.h"

void InitRock(Rock& rock)
{
	rock.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	rock.shape.setSize(sf::Vector2f(ROCK_SIZE, ROCK_SIZE));
	rock.shape.setFillColor(sf::Color::White);
	rock.shape.setOrigin(ROCK_SIZE / 2.0f, ROCK_SIZE / 2.0f);
	rock.shape.setPosition(rock.position.X, rock.position.Y);
}