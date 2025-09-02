#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameStateData.h"

namespace ArkanoidGame
{
	class GameStateRecordsData : public GameStateData
	{
		public:

			void HandleWindowEvent(const sf::Event& event) override;
			void Init() override;
			void Update(float deltaTime) override;
			void Draw(sf::RenderWindow& window) override;

		private:

			sf::Font font;

			sf::Text titleText;
			std::vector<sf::Text> tableTexts;
			sf::Text hintText;
	};
}

