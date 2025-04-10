#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		//Init player state
		player.position = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		//Init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.X, player.position.Y);
		window.draw(player.sprite);
	}

	void HandleInput(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			game.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			game.player.direction = PlayerDirection::Down;
		}
	}

	void UpdateInput(Game& game, float deltaTime)
	{
		switch (game.player.direction)
		{
			case PlayerDirection::Right:
			{
				game.player.position.X += game.player.speed * deltaTime;
				SetSpriteSize(game.player.sprite, PLAYER_SIZE, PLAYER_SIZE);
				game.player.sprite.setRotation(0.0f);
				break;
			}
			case PlayerDirection::Up:
			{
				game.player.position.Y -= game.player.speed * deltaTime;
				game.player.sprite.setRotation(-90.0f);
				break;
			}
			case PlayerDirection::Left:
			{
				game.player.position.X -= game.player.speed * deltaTime;
				SetSpriteSize(game.player.sprite, PLAYER_SIZE, PLAYER_SIZE * (-1.0f));
				game.player.sprite.setRotation(-180.0f);
				break;
			}
			case PlayerDirection::Down:
			{
				game.player.position.Y += game.player.speed * deltaTime;
				game.player.sprite.setRotation(90.0f);
				break;
			}
		}
	}
	
}