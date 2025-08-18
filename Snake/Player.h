#pragma once

#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2D position;
		float speed = INITIAL_SPEED;
		PlayerDirection direction = PlayerDirection::Right;
		sf::Sprite sprite;
	};

	struct Game;
	struct GameStatePlayingData;

	void InitPlayer(Player& player, const sf::Texture& texture);
	void DrawPlayer(Player& player, sf::RenderWindow& window);

	void HandleInput(GameStatePlayingData& data);
	void UpdateInput(GameStatePlayingData& data, float deltaTime);
}