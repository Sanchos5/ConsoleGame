#include "GameStatePlaying.h"
#include "Application.h"
#include "Block.h"
#include "Game.h"
#include "Math.h"
#include "assert.h"
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		//assert(data.soundAppleEatBuffer.loadFromFile(SOUNDS_PATH + "\\AppleEat.wav"));
		//assert(data.soundDeathBuffer.loadFromFile(SOUNDS_PATH + "\\GameOver.wav"));
		//assert(data.soundBackgroundBuffer.loadFromFile(SOUNDS_PATH + "\\Background.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(16);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString(L"Используйте клавишы A D для перемещения, ESC для выхода");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		gameObjects.emplace_back(std::make_shared<Platform>(sf::Vector2f({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f })));
		gameObjects.emplace_back(std::make_shared<Ball>(sf::Vector2f({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f })));
		createBlocks();

		//DifficultyLevelState(data);

		//data.sound.stop();

		/*soundBackground.setBuffer(soundBackgroundBuffer);
		if (Application::Instance().GetGame().IsEnableOptions(GameOptions::Music))
		{
			soundBackground.setLoop(true);
			soundBackground.play();
		}
		soundAppleEat.setBuffer(data.soundAppleEatBuffer);
		soundDeath.setBuffer(data.soundDeathBuffer);*/
	}

	/*void DifficultyLevelState(GameStatePlayingData& data)
	{
		if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Easy))
		{
			data.snake.speed = INITIAL_SPEED * 0.5f;
		}
		else if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Normal))
		{
			data.snake.speed = INITIAL_SPEED;
		}
		else if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Hard))
		{
			data.snake.speed = INITIAL_SPEED * 2.f;
		}
		else if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Insane))
		{
			data.snake.speed = INITIAL_SPEED * 3.f;
		}
		else if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Impossible))
		{
			data.snake.speed = INITIAL_SPEED * 4.f;
		}
	}*/

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float deltaTime)
	{
		static auto updateFunctor = [deltaTime](auto obj) { obj->Update(deltaTime); };

		std::for_each(gameObjects.begin(), gameObjects.end(), updateFunctor);
		std::for_each(blocks.begin(), blocks.end(), updateFunctor);

		std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);

		const bool isCollision = platform->CheckCollision(ball);

		bool needInverseDirX = false;
		bool needInverseDirY = false;
		bool hasBrokeOneBlock = false;

		//remove-erase idiom
		blocks.erase(
			std::remove_if(blocks.begin(), blocks.end(),
				[ball, &hasBrokeOneBlock, &needInverseDirX, &needInverseDirY, this](auto block) 
				{
					if ((!hasBrokeOneBlock) && block->CheckCollision(ball)) 
					{
						hasBrokeOneBlock = true;
						const auto ballPos = ball->GetPosition();
						const auto blockRect = block->GetRect();

						GetBallInverse(ballPos, blockRect, needInverseDirX, needInverseDirY);

						
						if (block->isHit == true)
						{
							score += 10;
						}
						
					}
					return block->IsBroken();
				}),
			blocks.end()
		);

		

		scoreText.setString(L"Счёт: " + std::to_wstring(score));
		
		if (needInverseDirX) 
		{
			ball->InvertDirectionX();
		}
		if (needInverseDirY) 
		{
			ball->InvertDirectionY();
		}

		const bool isGameWin = blocks.size() == 0;
		const bool isGameFinished = !isCollision && ball->GetPosition().y > platform->GetRect().top;
		Game& game = Application::Instance().GetGame();

		if (isGameWin)
		{
			game.PushState(GameStateType::GameWin, false);
		}
		else if(isGameFinished)
		{
			//gameOverSound.play();
			game.PushState(GameStateType::GameOver, false);
			game.UpdateRecord(PLAYER_NAME, score);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		static auto drawFunc = [&window](auto block) { block->Draw(window); };

		// Draw game objects
		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
		std::for_each(blocks.begin(), blocks.end(), drawFunc);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::createBlocks()
	{
		int row = 0;
		for (; row < BLOCKS_COUNT_ROWS; ++row) 
		{
			for (int col = 0; col < BLOCKS_COUNT_IN_ROW ; ++col) 
			{
				blocks.emplace_back(std::make_shared<SmoothDestroyableBlock>(sf::Vector2f({ BLOCK_SHIFT + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SHIFT), 100.f + row * BLOCK_HEIGHT })));
			}
		}
		for (int col = 0; col < BLOCKS_COUNT_IN_ROW; ++col)
		{
			blocks.emplace_back(std::make_shared<HeavyDestroyableBlock>(sf::Vector2f({ BLOCK_SHIFT + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SHIFT), 100.f + row * BLOCK_HEIGHT })));
		}
		for (int col = 0; col < 3; ++col) 
		{
			blocks.emplace_back(std::make_shared<UnbreackableBlock>(sf::Vector2f({ SCREEN_WIDTH / 2.f - BLOCK_WIDTH - BLOCK_SHIFT / 2.f + col * (BLOCK_WIDTH + BLOCK_SHIFT), 100.f + (row + 1) * BLOCK_HEIGHT })));
		}
	}

	void GameStatePlayingData::GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY) 
	{

		if (ballPos.y > blockRect.top + blockRect.height)
		{
			needInverseDirY = true;
		}
		if (ballPos.x < blockRect.left)
		{
			needInverseDirX = true;
		}
		if (ballPos.x > blockRect.left + blockRect.width)
		{
			needInverseDirX = true;
		}
	}
}