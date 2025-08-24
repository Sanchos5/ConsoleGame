#include "GameStateMainMenu.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		assert(data.soundBtnHover.loadFromFile(SOUNDS_PATH + "\\menu-hover.wav"));

		auto setTextParameters = [&data](sf::Text& itemText, const std::wstring& title, int fontSize, sf::Color color = sf::Color::Transparent)
			{
				itemText.setString(title);
				itemText.setFont(data.font);
				itemText.setCharacterSize(fontSize);
				if (color != sf::Color::Transparent)
				{
					itemText.setFillColor(color);
				}
			};

		setTextParameters(data.menu.rootItem.hintText, L"Змейка", 48, sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.recordsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		setTextParameters(data.startGameItem.text, L"Начать игру", 24);
		setTextParameters(data.optionsItem.text, L"Настройки", 24);
		setTextParameters(data.recordsItem.text, L"Таблица рекордов", 24);

		setTextParameters(data.optionsItem.hintText, L"Настройки", 48, sf::Color::Red);
		data.optionsItem.childrenOrientation = Orientation::Vertical;
		data.optionsItem.childrenAlignment = Alignment::Middle;
		data.optionsItem.childrenSpacing = 10.f;
		data.optionsItem.children.push_back(&data.optionsInfiniteApplesItem);
		data.optionsItem.children.push_back(&data.optionsWithAccelerationItem);

		//setTextParameters(data.recordsItem.hintText, "Records", 24, sf::Color::Red);


		setTextParameters(data.optionsInfiniteApplesItem.text, L"Infinite Apples: On/Off", 24);
		setTextParameters(data.optionsWithAccelerationItem.text, L"With Acceleration: On/Off", 24);
		setTextParameters(data.exitGameItem.text, L"Выйти из игры", 24);

		setTextParameters(data.exitGameItem.hintText, L"Are you sure?", 48, sf::Color::Red);
		data.exitGameItem.childrenOrientation = Orientation::Horizontal;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		setTextParameters(data.yesItem.text, L"Да", 24);
		setTextParameters(data.noItem.text, L"Нет", 24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				data.sound.setBuffer(data.soundBtnHover);
				data.sound.play();

				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.optionsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.optionsInfiniteApplesItem)
				{
					game.options = (GameModeOption)((std::uint8_t)game.options ^ (std::uint8_t)GameModeOption::InfinityApples);
				}
				else if (data.menu.selectedItem == &data.optionsWithAccelerationItem)
				{
					game.options = (GameModeOption)((std::uint8_t)game.options ^ (std::uint8_t)GameModeOption::AcceleratedPlayer);
				}
				else if (data.menu.selectedItem == &data.recordsItem)
				{
					PushGameState(game, GameStateType::Records, true);
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta)
	{
		bool isInfiniteApples = ((std::uint8_t)game.options & (std::uint8_t)GameModeOption::InfinityApples) != (std::uint8_t)GameModeOption::Empty;
		data.optionsInfiniteApplesItem.text.setString("Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));

		bool isWithAcceleration = ((std::uint8_t)game.options & (std::uint8_t)GameModeOption::AcceleratedPlayer) != (std::uint8_t)GameModeOption::Empty;
		data.optionsWithAccelerationItem.text.setString("With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}
}