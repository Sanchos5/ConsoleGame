#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Menu.h"

namespace ArkanoidGame
{
	class Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		Menu menu;

		sf::SoundBuffer soundBtnHoverBuffer;
		sf::Sound soundBtnHover;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window);
}

