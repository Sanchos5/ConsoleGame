#include "UI.h"
#include "Game.h"
#include <string>

namespace ApplesGame
{
	void InitUI(UIState& uiState, const sf::Font& font)
	{
		/*uiState.scoreText.setFont(font);
		uiState.scoreText.setCharacterSize(24);
		uiState.scoreText.setFillColor(sf::Color::Yellow);*/

		uiState.inputHintText.setFont(font);
		uiState.inputHintText.setCharacterSize(16);
		uiState.inputHintText.setFillColor(sf::Color::White);
		uiState.inputHintText.setString("Use arrow keys to move, Space to restart, ESC to exit");
		uiState.inputHintText.setOrigin(GetTextOrigin(uiState.inputHintText, { 1.f, 0.f }));


		uiState.isStartGameTextVisible = true;
		uiState.startGameText.setFont(font);
		uiState.startGameText.setCharacterSize(30);
		uiState.startGameText.setStyle(sf::Text::Bold);
		uiState.startGameText.setFillColor(sf::Color::Red);
		uiState.startGameText.setString("START GAME");
		uiState.startGameText.setOrigin(GetTextOrigin(uiState.startGameText, { 0.5f, 0.5f }));

		/*uiState.isGameOverTextVisible = false;
		uiState.gameOverText.setFont(font);
		uiState.gameOverText.setCharacterSize(48);
		uiState.gameOverText.setStyle(sf::Text::Bold);
		uiState.gameOverText.setFillColor(sf::Color::Red);
		uiState.gameOverText.setString("GAME OVER");
		uiState.gameOverText.setOrigin(GetTextOrigin(uiState.gameOverText, { 0.5f, 0.5f }));*/

		uiState.hintText.setFont(font);
		uiState.hintText.setCharacterSize(20);
		uiState.hintText.setStyle(sf::Text::Bold);
		uiState.hintText.setFillColor(sf::Color::White);
		uiState.hintText.setString("1 - select finite apple \n"
									"2 - select infinite apples \n"
									"3 - select accelerated player \n"
									"4 - select no accelerated player \n"
									"modes can be combined");
		uiState.hintText.setOrigin(GetTextOrigin(uiState.hintText, { 0.5f, 0.5f }));
	}

	void UpdateUI(UIState& uiState, const struct GameState& gameState, float timeDelta)
	{
		/*uiState.scoreText.setString("Apples eaten: " + std::to_string(gameState.numEatenApples));

		uiState.isGameOverTextVisible = gameState.isGameOver;
		sf::Color gameOverTextColor = (int)gameState.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		uiState.gameOverText.setFillColor(gameOverTextColor);*/
	}

	void DrawUI(UIState& uiState, sf::RenderWindow& window)
	{
		/*uiState.scoreText.setPosition(10.f, 10.f);
		window.draw(uiState.scoreText);

		uiState.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
		window.draw(uiState.inputHintText);

		if (uiState.isGameOverTextVisible)
		{
			uiState.gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			window.draw(uiState.gameOverText);
		}*/
	}

}