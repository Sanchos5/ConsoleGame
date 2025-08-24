#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;
		MenuItem optionsItem;
		MenuItem optionsInfiniteApplesItem;
		MenuItem optionsWithAccelerationItem;
		MenuItem recordsItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;

		sf::SoundBuffer soundBtnHover;
		sf::Sound sound;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
}