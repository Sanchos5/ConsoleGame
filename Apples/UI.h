#pragma once

#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct UIState
	{
		bool isStartGameTextVisible = true;
		bool isGameOverTextVisible = false;


		sf::Text startGameText;
		sf::Text gameOverText;

		sf::Text inputHintText;
		/*bool isGameOverTextVisible = false;

		sf::Text scoreText;
		sf::Text gameOverText;*/
	};

	void InitUI(UIState& uiState, const sf::Font& font);
	void UpdateUI(UIState& uiState, const struct GameState& gameState, float timeDelta);
	void DrawUI(UIState& uiState, sf::RenderWindow& window);
}