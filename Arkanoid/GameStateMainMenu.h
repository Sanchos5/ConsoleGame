#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Menu.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateMainMenuData : public GameStateData
	{
		public:

			void HandleWindowEvent(const sf::Event& event) override;
			void Init() override;
			void Update(float deltaTime) override;
			void Draw(sf::RenderWindow& window) override;

		private:

			sf::Font font;
			Menu menu;

			sf::SoundBuffer soundBtnHoverBuffer;
			sf::Sound soundBtnHover;
	};
}

