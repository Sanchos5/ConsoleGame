#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "UI.h"
#include <iostream>

namespace ApplesGame
{
	enum class GameModeOption : std::uint8_t
	{
		FiniteApples = 1 << 0, // 0001
		InfinityApples = 1 << 1, // 0010
		AcceleratedPlayer = 1 << 2, // 0100
		NoAcceleratedPlayer = 1 << 3, // 1000

		Default = InfinityApples,
		Empty = 0,
	};

	struct Game
	{
		std::vector<Apple> apples;

		sf::Event event;
		Player player;
		Apple apple;
		Rock rocks[NUM_ROCKS];
		UIState uiState;

		
		//Global game data
		int numApple = 10;
		int numEatenApples = 0;
		bool isGameFinished = false;
		float timeSinceGameFinished = 0.0f;
		bool isGameOverTextVisible = false;
		sf::RectangleShape background;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::SoundBuffer soundAppleEat;
		sf::SoundBuffer soundDeath;
		sf::Sound sound;

		sf::Font font;
		sf::Text scoreText;
		sf::Text gameOverText;

		GameModeOption gamemode = GameModeOption::Default;
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DrawUI(Game& uiState, sf::RenderWindow& window);
	void ChooseGameMode(Game& game);
	void DeinitializeGame(Game& game);
}
