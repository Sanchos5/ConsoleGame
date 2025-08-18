#include "GameStatePlaying.h"
#include "Game.h"
#include "assert.h"

namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init game resources (terminate if error)
		assert(data.playerTexture.loadFromFile(TEXTURES_PATH + "\\head.png"));

		assert(data.appleTexture.loadFromFile(TEXTURES_PATH + "\\apple.png"));
		assert(data.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

		//assert(data.soundAppleEat.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		//assert(data.soundDeath.loadFromFile(RESOURCES_PATH + "\\Death.wav"));

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		InitPlayer(data.player, data.playerTexture);

		for (int i = 0; i < data.numApple; ++i)
		{
			data.apples.resize(data.numApple);
			InitApple(data.apples[i], data.appleTexture);
		}

		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			
			//InitRock(data.rocks[i], data.rockTexture);
		}

		data.sound.stop();
		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::White);

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(16);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to exit");
		data.inputHintText.setOrigin(GetTextOrigin(data.inputHintText, { 1.f, 0.f }));
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
		if (!data.isGameFinished)
		{
			HandleInput(data);
			UpdateInput(data, deltaTime);

			for (int i = 0; i < data.numApple; ++i)
			{
				//Check collision for circle
				if (IsCirclesCollide(data.player.position, PLAYER_SIZE,
					data.apples[i].position, APPLE_SIZE))
				{
					if ((std::uint8_t)game.options & (std::uint8_t)GameModeOption::InfinityApples)
					{
						data.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1);
					}
					else
					{
						data.apples.erase(data.apples.begin() + i);
						data.apples.resize(data.numApple);
					}

					if ((std::uint8_t)game.options & (std::uint8_t)GameModeOption::AcceleratedPlayer)
					{
						data.player.speed += ACCELERATION;
					}

					data.sound.setBuffer(data.soundAppleEat);
					data.sound.play();
					++data.numEatenApples;
				}
			}

			for (int i = 0; i < NUM_ROCKS; ++i)
			{
				if (IsRectanglesCollide(data.player.position, { PLAYER_SIZE, PLAYER_SIZE },
					data.rocks[i].position, { ROCK_SIZE, ROCK_SIZE }))
				{
					data.sound.setBuffer(data.soundDeath);
					data.sound.play();
					data.isGameFinished = true;
					PushGameState(game, GameStateType::GameOver, false);
				}
			}
		}
		
		//check screen borders collision
		if (data.player.position.X - PLAYER_SIZE / 2.0f < 0.0f || data.player.position.X + PLAYER_SIZE / 2.0f > SCREEN_WIDTH ||
			data.player.position.Y - PLAYER_SIZE / 2.0f < 0.0f || data.player.position.Y + PLAYER_SIZE / 2.0f > SCREEN_HEIGHT)
		{
			// stop game
			if (!data.isGameFinished)
			{

				data.sound.setBuffer(data.soundDeath);
				data.sound.play();
				data.isGameFinished = true;
				PushGameState(game, GameStateType::GameOver, false);
			}
		}

		data.scoreText.setString("Apples eaten: " + std::to_string(data.numEatenApples));

		if (data.isGameFinished)
		{
			// Find player in records table and update his score
			for (RecordsTableItem& item : game.recordsTable)
			{
				if (item.name == "Player")
				{
					item.score = data.numEatenApples;
					break;
				}
			}

			// Sort records table
			std::sort(std::begin(game.recordsTable), std::end(game.recordsTable));

			PushGameState(game, GameStateType::GameOver, false);
		}

	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// Draw player
		DrawPlayer(data.player, window);

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