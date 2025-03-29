// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIGHT = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.0f;
const float PLAYER_SIZE = 20.0f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT, SCREEN_HEIGHT), "Apples game!");

	float playerX = SCREEN_WIGHT / 2.0f;
	float playerY = SCREEN_HEIGHT / 2.0f;
	float playerSpeed = INITIAL_SPEED;
	int playerDirection = 0; // 0 - Right, 1 - Up, 2 - Left, 3 - Down

	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Green);
	playerShape.setOrigin(PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f);
	playerShape.setPosition(playerX, playerY);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		playerShape.setPosition(playerX, playerY);
		window.draw(playerShape);
		window.display();
	}

	return 0;
}
