#include "Player.h"
#include "Game.h"
#include "GameStatePlaying.h"

namespace SnakeGame
{
	void InitPlayer(Player& player, const sf::Texture& texture)
	{
		//Init player state
		player.position = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		//Init player sprite
		player.sprite.setTexture(texture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.X, player.position.Y);
		window.draw(player.sprite);
	}

	void HandleInput(GameStatePlayingData& data)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			data.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			data.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			data.player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			data.player.direction = PlayerDirection::Down;
		}
	}

	void UpdateInput(GameStatePlayingData& data, float deltaTime)
	{
		switch (data.player.direction)
		{
			case PlayerDirection::Right:
			{
				data.player.position.X += data.player.speed * deltaTime;
				SetSpriteSize(data.player.sprite, PLAYER_SIZE, PLAYER_SIZE);
				data.player.sprite.setRotation(90.0f);
				break;
			}
			case PlayerDirection::Up:
			{
				data.player.position.Y -= data.player.speed * deltaTime;
				data.player.sprite.setRotation(0.0f);
				break;
			}
			case PlayerDirection::Left:
			{
				data.player.position.X -= data.player.speed * deltaTime;
				SetSpriteSize(data.player.sprite, PLAYER_SIZE, PLAYER_SIZE * (-1.0f));
				data.player.sprite.setRotation(-90.0f);
				break;
			}
			case PlayerDirection::Down:
			{
				data.player.position.Y += data.player.speed * deltaTime;
				data.player.sprite.setRotation(180.0f);
				break;
			}
		}
	}
	
}