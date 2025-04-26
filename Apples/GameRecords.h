#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace ApplesGame
{
	struct Game;

	struct GameRecordState
	{
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

	void InitGameRecord(GameRecordState& data, Game& game);
	void UpdateGameRecord(GameRecordState& data, Game& game, float timeDelta);
	void DrawGameRecord(GameRecordState& data, sf::RenderWindow& window);
}