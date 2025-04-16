
#include "Game.h"
#include <cassert>
#include <string>
#include <iostream>


namespace ApplesGame
{
	void DrawUI(Game& game, sf::RenderWindow& window)
	{
		game.scoreText.setPosition(10.f, 10.f);
		window.draw(game.scoreText);

		game.uiState.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
		window.draw(game.uiState.inputHintText);

		if (game.isGameOverTextVisible)
		{
			game.gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			window.draw(game.gameOverText);
		}

		if(game.uiState.isStartGameTextVisible)
		{
			game.uiState.startGameText.setPosition(window.getSize().x / 2.f, (window.getSize().y / 2.f) - 100.f);
			window.draw(game.uiState.startGameText);
		}
	}

	void InitGame(Game& game)
	{
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(game.soundAppleEat.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.soundDeath.loadFromFile(RESOURCES_PATH + "\\Death.wav"));

		assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		InitUI(game.uiState, game.font);

		game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.0f, 0.0f);

		game.scoreText.setFont(game.font);
		game.scoreText.setCharacterSize(24);
		game.scoreText.setFillColor(sf::Color::White);

		game.gameOverText.setFont(game.font);
		game.gameOverText.setCharacterSize(48);
		game.gameOverText.setStyle(sf::Text::Bold);
		game.gameOverText.setFillColor(sf::Color::Red);
		game.gameOverText.setString("GAME OVER");
		game.gameOverText.setOrigin(GetTextOrigin(game.gameOverText, { 0.5f, 0.5f }));

		//std::cout << "число €блок";
		//std::cin >> game.numApple;

		RestartGame(game);
	}

	void RestartGame(Game& game)
	{
		InitPlayer(game.player, game);

		for (int i = 0; i < NUM_APPLES; ++i)
		{
			InitApple(game.apples[i], game);
		}
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			InitRock(game.rocks[i], game);
		}

		//Paused
		game.numEatenApples = 0;
		game.isGameFinished = false;
		game.isGameOverTextVisible = false;
		game.timeSinceGameFinished = 0.0f;
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		if (!game.isGameFinished && !game.uiState.isStartGameTextVisible)
		{
			HandleInput(game);
			UpdateInput(game, deltaTime);

			//Find players collision with apples
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				//Check collision for circle
				if(IsCirclesCollide(game.player.position, PLAYER_SIZE,
					game.apples[i].position, APPLE_SIZE))
				{
					game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1);
					game.sound.setBuffer(game.soundAppleEat);
					game.sound.play();
					++game.numEatenApples;
				}
			}
			for (int i = 0; i < NUM_ROCKS; ++i)
			{
				if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
					game.rocks[i].position, { ROCK_SIZE, ROCK_SIZE }))
				{
					game.sound.setBuffer(game.soundDeath);
					game.sound.play();
					game.isGameFinished = true;
					game.timeSinceGameFinished = FINISHED_LENGTH;
				}
			}

			game.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));
		}

		if(game.uiState.isStartGameTextVisible)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				game.uiState.isStartGameTextVisible = false;
			}
		}

		if (game.isGameFinished)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				RestartGame(game);
			}
			else
			{
				game.isGameOverTextVisible = true;
			}
		}

		//check screen borders collision
		if (game.player.position.X - PLAYER_SIZE / 2.0f < 0.0f || game.player.position.X + PLAYER_SIZE / 2.0f > SCREEN_WIDTH ||
			game.player.position.Y - PLAYER_SIZE / 2.0f < 0.0f || game.player.position.Y + PLAYER_SIZE / 2.0f > SCREEN_HEIGHT)
		{
			// stop game
			if (!game.isGameFinished)
			{
				game.sound.setBuffer(game.soundDeath);
				game.sound.play();
				
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
			game.apples[i].sprite.setPosition(game.apples[i].position.X, game.apples[i].position.Y);
			window.draw(game.apples[i].sprite);
		}
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			game.rocks[i].sprite.setPosition(game.rocks[i].position.X, game.rocks[i].position.Y);
			window.draw(game.rocks[i].sprite);
		}

		DrawUI(game, window);
	}

	void DeinitializeGame(Game& game)
	{

	}
}

