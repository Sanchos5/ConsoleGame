#include "Player.h"
#include "Game.h"

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
