#include "GameStatePlaying.h"
#include "Game.h"
#include "assert.h"
#include <sstream>

namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init game resources (terminate if error)
		LoadSnakeTextures(data.snake);

		assert(data.appleTexture.loadFromFile(TEXTURES_PATH + "\\apple.png"));
		assert(data.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

		assert(data.soundAppleEat.loadFromFile(SOUNDS_PATH + "\\AppleEat.wav"));
		assert(data.soundDeath.loadFromFile(SOUNDS_PATH + "\\GameOver.wav"));
		assert(data.soundBackground.loadFromFile(SOUNDS_PATH + "\\Background.wav"));

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		// Init background
		data.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		data.background.setPosition(0.f, 0.f);
		data.background.setFillColor(sf::Color(0, 200, 0));

		InitPlayer(data.snake);

		for (int i = 0; i < data.numApple; ++i)
		{
			data.apples.resize(data.numApple);
			InitApple(data.apples[i], data.appleTexture);
		}

		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			
			InitRock(data.rocks[i], data.rockTexture);
		}

		//data.sound.stop();
		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::White);

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(16);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to exit");
		data.inputHintText.setOrigin(GetTextOrigin(data.inputHintText, { 1.f, 0.f }));

		data.soundBack.setBuffer(data.soundBackground);
		data.soundBack.setLoop(true);
		data.soundBack.play();

		if (game.difficulty == DifficultyLevel::Easy)
		{
			data.snake.speed = INITIAL_SPEED * 0.5f;
		}
		else if (game.difficulty == DifficultyLevel::Normal)
		{
			data.snake.speed = INITIAL_SPEED;
		}
		else if (game.difficulty == DifficultyLevel::Hard)
		{
			data.snake.speed = INITIAL_SPEED * 2.f;
		}
		else if (game.difficulty == DifficultyLevel::Insane)
		{
			data.snake.speed = INITIAL_SPEED * 3.f;
		}
		else if (game.difficulty == DifficultyLevel::Impossible)
		{
			data.snake.speed = INITIAL_SPEED * 4.f;
		}
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime)
	{
		HandleInput(data.snake);
		UpdateInput(data.snake, deltaTime);

		for (int i = 0; i < data.numApple; ++i)
		{
			//Check collision for circle
			if (CheckSpriteIntersection(*data.snake.head, data.apples[i].sprite))
			{
				GrowSnake(data.snake);

				if (game.difficulty == DifficultyLevel::Easy)
				{
					data.numEatenApples += 1;
				}
				else if (game.difficulty == DifficultyLevel::Normal)
				{
					data.numEatenApples += 2;
				}
				else if (game.difficulty == DifficultyLevel::Hard)
				{
					data.numEatenApples += 3;
				}
				else if (game.difficulty == DifficultyLevel::Insane)
				{
					data.numEatenApples += 4;
				}
				else if (game.difficulty == DifficultyLevel::Impossible)
				{
					data.numEatenApples += 5;
				}

				//data.numEatenApples++;
				data.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50);

				if ((std::uint8_t)game.options & (std::uint8_t)GameModeOption::AcceleratedPlayer) {
					data.snake.speed += ACCELERATION;
				}


				data.sound.setBuffer(data.soundAppleEat);
				data.sound.play();
			}
		}

		data.scoreText.setString("Apples eaten: " + std::to_string(data.numEatenApples));

		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			if (data.isGameFinished
				|| !HasSnakeCollisionWithRect(data.snake, data.background.getGlobalBounds()) // Check collision with screen border
				|| CheckSnakeCollisionWithHimself(data.snake)		// Check collision with screen border
				|| CheckSpriteIntersection(*data.snake.head, data.rocks[i].sprite)) // Check collision with rocks)
			{

				// Find snake in records table and update his score
				/*for (RecordsTableItem& item : game.recordsTable)
				{
					if (item.name == "Player")
					{
						item.score = data.numEatenApples;
						break;
					}
				}*/

				// Find snake in records table and update his score
				game.recordsTable[PLAYER_NAME] = std::max(game.recordsTable[PLAYER_NAME], data.numEatenApples);

				// Sort records table
				//std::sort(std::begin(game.recordsTable), std::end(game.recordsTable));

				data.soundBack.stop();
				data.sound.setBuffer(data.soundDeath);
				data.sound.play();
				PushGameState(game, GameStateType::GameOver, false);
			}
		}
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// Draw snake
		DrawPlayer(data.snake, window);

		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}

		for (Rock& rock : data.rocks)
		{
			DrawRock(rock, window);
		}

		data.scoreText.setPosition(10.f, 10.f);
		window.draw(data.scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(data.inputHintText);
	}
}