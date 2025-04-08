
#include "Game.h"
#include <cassert>

void RestartGame(Game& game)
{
	InitPlayer(game.player, game);

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		InitApple(game.apples[i]);
	}

	//Paused
	game.numEatenApples = 0;
	game.isGameFinished = false;
	game.timeSinceGameFinished = 0.0f;
}

void InitGame(Game& game)
{
	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));

	game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	game.background.setFillColor(sf::Color::Black);
	game.background.setPosition(0.0f, 0.0f);

	RestartGame(game);
}

void UpdateGame(Game& game, float deltaTime)
{
	if (!game.isGameFinished)
	{
		//Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			game.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			game.player.direction = PlayerDirection::Down;
		}

		//Update player state
		switch (game.player.direction)
		{
		case PlayerDirection::Right:
		{
			game.player.position.X += game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			game.player.position.Y -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			game.player.position.X -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			game.player.position.Y += game.player.speed * deltaTime;
			break;
		}
		}

		//Find players collision with apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.apples[i].position, { APPLE_SIZE, APPLE_SIZE }))
			{
				game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				++game.numEatenApples;
				game.player.speed += ACCELERATION * deltaTime;
			}

			//Check collision for circle

			/*if(IsCirclesCollide(game.playerPosition, PLAYER_SIZE / 2.0f,
				game.applesPosition[i], APPLE_SIZE / 2.0f))
			{
				++game.numEatenApples;
			}*/
		}
	}

	if (game.isGameFinished)
	{
		game.timeSinceGameFinished -= deltaTime;

		if (game.timeSinceGameFinished <= 0.0f)
		{
			game.background.setFillColor(sf::Color::Black);

			RestartGame(game);
		}
		else
		{
			game.background.setFillColor(sf::Color::Red);
		}
	}

	//check screen borders collision
	if (game.player.position.X - PLAYER_SIZE / 2.0f < 0.0f || game.player.position.X + PLAYER_SIZE / 2.0f > SCREEN_WIDTH ||
		game.player.position.Y - PLAYER_SIZE / 2.0f < 0.0f || game.player.position.Y + PLAYER_SIZE / 2.0f > SCREEN_HEIGHT)
	{
		// stop game
		if (!game.isGameFinished)
		{
			game.isGameFinished = true;
			game.timeSinceGameFinished = FINISHED_LENGTH;
		}
	}
}

void DrawGame(Game& game, sf::RenderWindow& window)
{
	window.draw(game.background);
	DrawPlayer(game.player, window);

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		game.apples[i].shape.setPosition(game.apples[i].position.X, game.apples[i].position.Y);
		window.draw(game.apples[i].shape);
	}
	
}

void DeinitializeGame(Game& game)
{

}
