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
const float FINISHED_LENGTH = 3.0f;

struct Vector2D
{
	float X = 0.0f;
	float Y = 0.0f;
};

enum class PlayerDirection
{
	Right = 0,
	Up,
	Left,
	Down
};

typedef Vector2D Position2D;

Position2D GetRandomPositionInScreen()
{
	Position2D result;
	result.X = rand() / (float)RAND_MAX * SCREEN_WIGHT;
	result.Y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
	return result;
}

bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, 
							Position2D rect2Position, Vector2D rect2Size)
{
	float dx = fabs(rect1Position.X - rect2Position.X);
	float dy = fabs(rect1Position.Y - rect2Position.Y);

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

struct Player
{
	Position2D position;
	float speed = INITIAL_SPEED;
	PlayerDirection direction = PlayerDirection::Right;
	sf::RectangleShape shape;
};

void InitPlayer(Player& player)
{
	//Init player state
	player.position = { SCREEN_WIGHT / 2.0f, SCREEN_HEIGHT / 2.0f };
	player.speed = INITIAL_SPEED;
	player.direction = PlayerDirection::Right;

	//Init player shape
	player.shape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	player.shape.setFillColor(sf::Color::Green);
	player.shape.setOrigin(PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f);
	player.shape.setPosition(player.position.X, player.position.Y);
}

struct Apple
{
	Position2D position;
	sf::CircleShape shape;
};

void InitApple(Apple& apple)
{
	apple.position = GetRandomPositionInScreen();

	apple.shape.setRadius(APPLE_SIZE / 2.0f);
	apple.shape.setFillColor(sf::Color::Red);
	apple.shape.setOrigin(APPLE_SIZE / 2.0f, APPLE_SIZE / 2.0f);
	apple.shape.setPosition(apple.position.X, apple.position.Y);
}

struct GameState
{
	Player player;
	Apple apples[NUM_APPLES];

	//Global game data
	int numEatenApples = 0;
	bool isPaused = false;
	float PauseTimeLeft = 0.0f;
	sf::RectangleShape background;
};

void RestartGame(GameState& gameState)
{
	InitPlayer(gameState.player);

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		InitApple(gameState.apples[i]);
	}

	//Paused
	gameState.numEatenApples = 0;
	gameState.isPaused = false;
	gameState.PauseTimeLeft = 0.0f;
}

void InitGame(GameState& gameState)
{
	gameState.background.setSize(sf::Vector2f(SCREEN_WIGHT, SCREEN_HEIGHT));
	gameState.background.setFillColor(sf::Color::Black);
	gameState.background.setPosition(0.0f, 0.0f);

	RestartGame(gameState);
}

void UpdateGame(GameState& gameState, float deltaTime)
{
	if (!gameState.isPaused)
	{
		//Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameState.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gameState.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameState.player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gameState.player.direction = PlayerDirection::Down;
		}

		//Update player state
		switch (gameState.player.direction)
		{
		case PlayerDirection::Right:
		{
			gameState.player.position.X += gameState.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			gameState.player.position.Y -= gameState.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			gameState.player.position.X -= gameState.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			gameState.player.position.Y += gameState.player.speed * deltaTime;
			break;
		}
		}

		//Find players collision with apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (IsRectanglesCollide(gameState.player.position, { PLAYER_SIZE, PLAYER_SIZE }, 
									gameState.apples[i].position, {APPLE_SIZE, APPLE_SIZE}))
			{
				gameState.apples[i].position = GetRandomPositionInScreen();
				++gameState.numEatenApples;
				gameState.player.speed += ACCELERATION * deltaTime;
			}

			//Check collision for circle
			
			/*if(IsCirclesCollide(gameState.playerPosition, PLAYER_SIZE / 2.0f,
				gameState.applesPosition[i], APPLE_SIZE / 2.0f))
			{
				++gameState.numEatenApples;
			}*/
		}
	}

	if (gameState.isPaused)
	{
		gameState.PauseTimeLeft -= deltaTime;

		if (gameState.PauseTimeLeft <= 0.0f)
		{
			gameState.background.setFillColor(sf::Color::Black);

			RestartGame(gameState);
		}
		else
		{
			gameState.background.setFillColor(sf::Color::Red);
		}
	}

	//check screen borders collision
	if (gameState.player.position.X - PLAYER_SIZE / 2.0f < 0.0f || gameState.player.position.X + PLAYER_SIZE / 2.0f > SCREEN_WIGHT ||
		gameState.player.position.Y - PLAYER_SIZE / 2.0f < 0.0f || gameState.player.position.Y + PLAYER_SIZE / 2.0f > SCREEN_HEIGHT)
	{
		// stop game
		if (!gameState.isPaused)
		{
			gameState.isPaused = true;
			gameState.PauseTimeLeft = FINISHED_LENGTH;
		}
	}
}

void DrawGame(GameState& gameState, sf::RenderWindow& window)
{
	window.draw(gameState.background);
	gameState.player.shape.setPosition(gameState.player.position.X, gameState.player.position.Y);
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		gameState.apples[i].shape.setPosition(gameState.apples[i].position.X, gameState.apples[i].position.Y);
		window.draw(gameState.apples[i].shape);
	}
	window.draw(gameState.player.shape);
}

int main()
{
	//Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT, SCREEN_HEIGHT), "Apples game!");

	int seed = (int)time(nullptr);
	srand(seed);

	GameState gameState;
	InitGame(gameState);

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
			{
				window.close();
				break;
			}
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}
		}

		UpdateGame(gameState, deltaTime);

		window.clear();
		DrawGame(gameState, window);
		window.display();
	}

	return 0;
}
