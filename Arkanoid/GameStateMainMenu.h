#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Menu.h"

namespace ArkanoidGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;

		MenuItem difficultyItem;
		MenuItem difficultyEasyItem;
		MenuItem difficultyNormalItem;
		MenuItem difficultyHardItem;
		MenuItem difficultyInsaneItem;
		MenuItem difficultyImpossibleItem;

		MenuItem optionsItem;
		MenuItem optionsSoundItem;
		MenuItem optionsMusicItem;

		MenuItem recordsItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;

		sf::SoundBuffer soundBtnHoverBuffer;
		sf::Sound soundBtnHover;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
}

