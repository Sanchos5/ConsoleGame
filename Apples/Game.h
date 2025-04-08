#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"

struct Game
{
	Player player;
	Apple apples[NUM_APPLES];
	Rock rocks[NUM_ROCKS];

	//Global game data
	int numEatenApples = 0;
	bool isGameFinished = false;
	float timeSinceGameFinished = 0.0f;
	sf::RectangleShape background;

	sf::Texture playerTexture;
};

void RestartGame(Game& game);
void InitGame(Game& game);
void UpdateGame(Game& game, float deltaTime);
void DrawGame(Game& game, sf::RenderWindow& window);
void DeinitializeGame(Game& game);