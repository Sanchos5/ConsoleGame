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
	struct Game
	{
		std::vector<Apple> apples;

		
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
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DrawUI(Game& uiState, sf::RenderWindow& window);
	void DeinitializeGame(Game& game);
}
