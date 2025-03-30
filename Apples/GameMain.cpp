// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIGHT = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.0f; //Pixels per second
const float PLAYER_SIZE = 20.0f;
const float ACCELERATION = 10.0f;
const int NUM_APPLES = 20;
const float APPLE_SIZE = 20.0f;

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);

	//Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT, SCREEN_HEIGHT), "Apples game!");

	//Init player state
	float playerX = SCREEN_WIGHT / 2.0f;
	float playerY = SCREEN_HEIGHT / 2.0f;
	float playerSpeed = INITIAL_SPEED;
	int playerDirection = 0; // 0 - Right, 1 - Up, 2 - Left, 3 - Down

	//Init player shape
	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Green);
	playerShape.setOrigin(PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f);
	playerShape.setPosition(playerX, playerY);

	//Init apples
	float applesX[NUM_APPLES];
	float applesY[NUM_APPLES];

	//Paused
	bool isPaused = false;
	float PauseTime = 5.0f;
	float PauseTimeLeft;

	//Init apples shape
	sf::CircleShape applesShape[NUM_APPLES];

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		//isApplesEaten[i] = false;
		applesX[i] = rand() / (float)RAND_MAX * SCREEN_WIGHT;
		applesY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

		applesShape[i].setRadius(APPLE_SIZE / 2.0f);
		applesShape[i].setFillColor(sf::Color::Red);
		applesShape[i].setOrigin(APPLE_SIZE / 2.0f, APPLE_SIZE / 2.0f);
		applesShape[i].setPosition(applesX[i], applesY[i]);
	}

	int numEatenApples = 0;

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		//calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if(!isPaused)
		{
			//Handle input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerDirection = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				playerDirection = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerDirection = 2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				playerDirection = 3;
			}

			//Update player state
			if (playerDirection == 0)
			{
				playerX += playerSpeed * deltaTime;
			}
			else if (playerDirection == 1)
			{
				playerY -= playerSpeed * deltaTime;
			}
			else if (playerDirection == 2)
			{
				playerX -= playerSpeed * deltaTime;
			}
			else if (playerDirection == 3)
			{
				playerY += playerSpeed * deltaTime;
			}

			//Find players collision with apples
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				//Check collision for square
				float dx = fabs(playerX - applesX[i]);
				float dy = fabs(playerY - applesY[i]);

				if (dx <= (APPLE_SIZE + PLAYER_SIZE) / 2.0f &&
					dy <= (APPLE_SIZE + PLAYER_SIZE) / 2.0f)
				{
					applesX[i] = rand() / (float)RAND_MAX * SCREEN_WIGHT;
					applesY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

					applesShape[i].setPosition(applesX[i], applesY[i]);
					++numEatenApples;

					playerSpeed += ACCELERATION * deltaTime;
				}

				//Check collision for circle
				/*float squareDistance = (playerX - applesX[i]) * (playerX - applesX[i]) +
					(playerY - applesY[i]) * (playerY - applesY[i]);
				float squareRadisuSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;
				if(squareDistance <= squareRadisuSum)
				{
					isApplesEaten[i] = true;
					++numEatenApples;
				}*/
			}
		}

		if (isPaused)
		{
			PauseTimeLeft -= deltaTime;

			if (PauseTimeLeft <= 0.0f)
			{
				isPaused = false;
				playerX = SCREEN_WIGHT / 2.0f;
				playerY = SCREEN_HEIGHT / 2.0f;

				for (int i = 0; i < NUM_APPLES; ++i)
				{
					applesX[i] = rand() / (float)RAND_MAX * SCREEN_WIGHT;
					applesY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
					applesShape[i].setPosition(applesX[i], applesY[i]);
				}

				int numEatenApples = 0;
				playerSpeed = INITIAL_SPEED;
			}
		}
		
		//check screen borders collision
		if (playerX - PLAYER_SIZE / 2.0f < 0.0f || playerX + PLAYER_SIZE / 2.0f > SCREEN_WIGHT || 
			playerY - PLAYER_SIZE / 2.0f < 0.0f || playerY + PLAYER_SIZE / 2.0f > SCREEN_HEIGHT)
		{
			// stop game
			if(!isPaused)
			{
				isPaused = true;
				PauseTimeLeft = PauseTime;
			}
		}

		window.clear();
		playerShape.setPosition(playerX, playerY);
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			window.draw(applesShape[i]);
		}
		window.draw(playerShape);
		window.display();
	}

	return 0;
}
