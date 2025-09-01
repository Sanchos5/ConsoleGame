#include "GameStatePlaying.h"
#include "Application.h"
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
		inputHintText.setString(L"»спользуйте клавишы WASD дл€ перемещени€, ESC дл€ выхода");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		platform.Init();
		ball.Init();

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
		platform.Update(deltaTime);
		ball.Update(deltaTime);

		const bool isCollision = platform.CheckCollisionWithBall(ball);
		if (isCollision) {
			ball.ReboundFromPlatform();
		}

		const bool isGameFinished = !isCollision && ball.GetPosition().y > platform.GetRect().top;

		if (isGameFinished)
		{
			//gameOverSound.play();

			Game& game = Application::Instance().GetGame();

			// Find player in records table and update his score
			//game.UpdateRecord(PLAYER_NAME, numEatenApples);
			game.PushState(GameStateType::GameOver, false);
		}

		//for (int i = 0; i < data.numApple; ++i)
		//{
		//	//Check collision for circle
		//	if (CheckSpriteIntersection(*data.snake.head, data.apples[i].sprite))
		//	{
		//		GrowSnake(data.snake);

		//		if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Easy))
		//		{
		//			data.numEatenApples += 1;
		//		}
		//		else if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Normal))
		//		{
		//			data.numEatenApples += 2;
		//		}
		//		else if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Hard))
		//		{
		//			data.numEatenApples += 3;
		//		}
		//		else if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Insane))
		//		{
		//			data.numEatenApples += 4;
		//		}
		//		else if (Application::Instance().GetGame().IsEnableDifficultyLevel(DifficultyLevel::Impossible))
		//		{
		//			data.numEatenApples += 5;
		//		}

		//		//data.numEatenApples++;
		//		data.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50);
		//		data.snake.speed += ACCELERATION;

		//		if (Application::Instance().GetGame().IsEnableOptions(GameOptions::Sound))
		//		{
		//			data.soundAppleEat.play();
		//		}
		//	}
		//}

		//scoreText.setString(L"—ъедено €блок: " + std::to_wstring(data.numEatenApples));
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw game objects
		platform.Draw(window);
		ball.Draw(window);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}