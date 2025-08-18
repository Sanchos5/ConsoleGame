// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

//#include "iostream"
#include <SFML/Graphics.hpp>
#include <cstdlib>
//#include <SFML/Audio.hpp>

#include "Game.h"

using namespace SnakeGame;

int main()
{
	// Init random number generator
	unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	//Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake game!");

	// We now use too much memory for stack, so we need to allocate it on heap
	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

	// Init game clock
	sf::Clock gameClock;
	sf::Time lastTime = gameClock.getElapsedTime();

	while (window.isOpen())
	{
		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		//calculate time delta
		sf::Time currentTime = gameClock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - lastTime.asSeconds();
		lastTime = currentTime;

		if(UpdateGame(*game, deltaTime))
		{
			// Draw everything here
			// Clear the window first
			window.clear();
			DrawGame(*game, window);

			// End the current frame, display window contents on screen
			window.display();
		}
		else
		{
			window.close();
		}

			
		//UpdateGame(*game, deltaTime);
	}

	ShutdownGame(*game);
	delete game;
	game = nullptr;

	return 0;
}
