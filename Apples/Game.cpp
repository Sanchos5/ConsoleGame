
#include "Game.h"
#include <cassert>
#include <string>
#include <algorithm>


namespace ApplesGame
{
	const char* PLAYER_NAME = "Player";

	void ChooseGameMode(Game& game)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			game.gamemode = static_cast<GameModeOption>(static_cast<int>(game.gamemode) 
				& ~static_cast<int>(GameModeOption::InfinityApples) | static_cast<int>(GameModeOption::FiniteApples));
			//game.gamemode = GameModeOption::FiniteApples;
			game.numApple = 20;
			game.apples.push_back(game.apple);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			game.gamemode = static_cast<GameModeOption>(static_cast<int>(game.gamemode)
				& ~static_cast<int>(GameModeOption::FiniteApples) | static_cast<int>(GameModeOption::InfinityApples));
			//game.gamemode = GameModeOption::InfinityApples;
			game.numApple = 20;
			game.apples.push_back(game.apple);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			game.gamemode = static_cast<GameModeOption>(static_cast<int>(game.gamemode)
				& ~static_cast<int>(GameModeOption::NoAcceleratedPlayer) | static_cast<int>(GameModeOption::AcceleratedPlayer));
			//game.gamemode = GameModeOption::AcceleratedPlayer;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			static_cast<GameModeOption>(static_cast<int>(game.gamemode)
				& ~static_cast<int>(GameModeOption::AcceleratedPlayer) | static_cast<int>(GameModeOption::NoAcceleratedPlayer));
			//game.gamemode = GameModeOption::NoAcceleratedPlayer;
		}
	}

	void DrawUI(Game& game, sf::RenderWindow& window)
	{
		game.scoreText.setPosition(10.f, 10.f);
		window.draw(game.scoreText);

		game.uiState.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
		window.draw(game.uiState.inputHintText);

		if (game.isGameOverTextVisible)
		{
			game.gameOverText.setPosition(window.getSize().x / 2.f, 50.0f);
			window.draw(game.gameOverText);

			if (game.numEatenApples > game.leaderboads[PLAYER_NAME])
			{
				game.leaderboads[PLAYER_NAME] = game.numEatenApples;

			}

			InitGameRecord(game.recordsState, game);

			DrawGameRecord(game.recordsState, window);
		}

		if(game.uiState.isStartGameTextVisible)
		{
			game.uiState.startGameText.setPosition(window.getSize().x / 2.f, (window.getSize().y / 2.f) - 100.f);
			window.draw(game.uiState.startGameText);

			game.uiState.hintText.setPosition(window.getSize().x / 2.f, (window.getSize().y / 2.f));
			window.draw(game.uiState.hintText);
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

		game.leaderboads =
		{
			{"Alice", rand() % 10},
			{"Bob", rand() % 10},
			{"Carol", rand() % 10},
			{"Dave", rand() % 10},
			{"John", rand() % 10},
		};
		
		InitUI(game.uiState, game.font);
		//InitGameRecord(game.recordsState, game);

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

		
		RestartGame(game);
	}

	void RestartGame(Game& game)
	{
		InitPlayer(game.player, game);

		for (int i = 0; i < game.numApple; ++i)
		{
			game.apples.resize(game.numApple);
			InitApple(game.apples[i], game);
		}

		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			InitRock(game.rocks[i], game);
		}

		//Paused
		game.sound.stop();
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

			for (int i = 0; i < game.numApple; ++i)
			{
				//Check collision for circle
				if(IsCirclesCollide(game.player.position, PLAYER_SIZE,
					game.apples[i].position, APPLE_SIZE))
				{
					if(static_cast<int>(game.gamemode) & static_cast<int>(GameModeOption::FiniteApples))
					{
						game.apples.erase(game.apples.begin() + i);
						game.apples.resize(game.numApple);
					}
					else if(static_cast<int>(game.gamemode) & static_cast<int>(GameModeOption::InfinityApples))
					{
						game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1);
					}
					
					if (static_cast<int>(game.gamemode) & static_cast<int>(GameModeOption::NoAcceleratedPlayer))
					{
						game.player.speed = INITIAL_SPEED;
					}
					else if (static_cast<int>(game.gamemode) & static_cast<int>(GameModeOption::AcceleratedPlayer))
					{
						game.player.speed += ACCELERATION;
					}
					
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
				}
			}

			game.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));
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
			}
		}

		if(game.uiState.isStartGameTextVisible)
		{
			ChooseGameMode(game);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				game.uiState.isStartGameTextVisible = false;
				game.apples.resize(game.numApple);

				for (int i = 0; i < game.numApple; ++i)
				{
					InitApple(game.apples[i], game);
				}
				
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
				/*if(game.numEatenApples > game.leaderboads[PLAYER_NAME])
				{
					game.leaderboads[PLAYER_NAME] = game.numEatenApples;
				}*/
				//InitGameRecord(game.recordsState, game);
				game.isGameOverTextVisible = true;
			}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.background);
		DrawPlayer(game.player, window);

		if (!game.uiState.isStartGameTextVisible)
		{
			for (int i = 0; i < game.numApple; ++i)
			{
				game.apples[i].sprite.setPosition(game.apples[i].position.X, game.apples[i].position.Y);
				window.draw(game.apples[i].sprite);
			}
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

