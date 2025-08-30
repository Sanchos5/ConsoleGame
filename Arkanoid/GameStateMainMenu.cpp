#include "GameStateMainMenu.h"
#include "Application.h"
#include <assert.h>

namespace ArkanoidGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data)
	{
		assert(data.font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		assert(data.soundBtnHoverBuffer.loadFromFile(SOUNDS_PATH + "\\menu-hover.wav"));

		data.soundBtnHover.setBuffer(data.soundBtnHoverBuffer);

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

		Game& game = Application::Instance().GetGame();
		MenuItem startGame;
		setTextParameters(startGame.text, L"Начать игру", 24);
		startGame.onPressCallback = [](MenuItem&)
			{
				SwitchGameState(Application::Instance().GetGame(), GameStateType::Playing);
			};

		//MenuItem difficultyEasy;
		setTextParameters(data.difficultyEasy.text, L"Лёгкий: " + std::wstring(game.difficulty == DifficultyLevel::Easy ? L"Вкл" : L"Выкл"), 24);
		data.difficultyEasy.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Easy;
				item.text.setString(L"Лёгкий: " + std::wstring(game.difficulty == DifficultyLevel::Easy ? L"Вкл" : L"Выкл"));
				
			};

		//MenuItem difficultyNormal;
		setTextParameters(data.difficultyNormal.text, L"Нормальный: " + std::wstring(game.difficulty == DifficultyLevel::Normal ? L"Вкл" : L"Выкл"), 24);
		data.difficultyNormal.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Normal;
				item.text.setString(L"Нормальный: " + std::wstring(game.difficulty == DifficultyLevel::Normal ? L"Вкл" : L"Выкл"));
			};

		//MenuItem difficultyHard;
		setTextParameters(data.difficultyHard.text, L"Сложный: " + std::wstring(game.difficulty == DifficultyLevel::Hard ? L"Вкл" : L"Выкл"), 24);
		data.difficultyHard.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Hard;
				item.text.setString(L"Сложный: " + std::wstring(game.difficulty == DifficultyLevel::Hard ? L"Вкл" : L"Выкл"));
			};

		//MenuItem difficultyInsane;
		setTextParameters(data.difficultyInsane.text, L"Безумный: " + std::wstring(game.difficulty == DifficultyLevel::Insane ? L"Вкл" : L"Выкл"), 24);
		data.difficultyInsane.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Insane;
				item.text.setString(L"Безумный: " + std::wstring(game.difficulty == DifficultyLevel::Insane ? L"Вкл" : L"Выкл"));
			};

		//MenuItem difficultyImpossible;
		setTextParameters(data.difficultyImpossible.text, L"Невозможный: " + std::wstring(game.difficulty == DifficultyLevel::Impossible ? L"Вкл" : L"Выкл"), 24);
		data.difficultyImpossible.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.difficulty = DifficultyLevel::Impossible;
				item.text.setString(L"Невозможный: " + std::wstring(game.difficulty == DifficultyLevel::Impossible ? L"Вкл" : L"Выкл"));
			};

		MenuItem difficulty;
		setTextParameters(difficulty.text, L"Уровень сложности", 24);
		setTextParameters(difficulty.hintText, L"Выберите уровень сложности", 48, sf::Color::Red);
		difficulty.childrenOrientation = Orientation::Vertical;
		difficulty.childrenAlignment = Alignment::Middle;
		difficulty.childrenSpacing = 10.f;
		difficulty.childrens.push_back(data.difficultyEasy);
		difficulty.childrens.push_back(data.difficultyNormal);
		difficulty.childrens.push_back(data.difficultyHard);
		difficulty.childrens.push_back(data.difficultyInsane);
		difficulty.childrens.push_back(data.difficultyImpossible);
		
		bool isSound = IsEnableOptions(Application::Instance().GetGame(), GameOptions::Sound);
		MenuItem optionsSound;
		setTextParameters(optionsSound.text, L"Звук: " + std::wstring(isSound ? L"Вкл" : L"Выкл"), 24);
		optionsSound.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::Sound);
				bool isSound = IsEnableOptions(game, GameOptions::Sound);
				item.text.setString(L"Звук: " + std::wstring(isSound ? L"Вкл" : L"Выкл"));
			};

		bool isMusic = IsEnableOptions(Application::Instance().GetGame(), GameOptions::Music);
		MenuItem optionsMusic;
		setTextParameters(optionsMusic.text, L"Музыка: " + std::wstring(isMusic ? L"Вкл" : L"Выкл"), 24);
		optionsMusic.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::Music);
				bool isMusic = IsEnableOptions(game, GameOptions::Music);
				item.text.setString(L"Музыка: " + std::wstring(isMusic ? L"Вкл" : L"Выкл"));
			};
		
		MenuItem options;
		setTextParameters(options.text, L"Настройки", 24);
		setTextParameters(options.hintText, L"Настройки", 48, sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;

		options.childrens.push_back(optionsSound);
		options.childrens.push_back(optionsMusic);
		

		MenuItem records;
		setTextParameters(records.text, L"Таблица рекордов", 24);
		records.onPressCallback = [](MenuItem&)
			{
				PushGameState(Application::Instance().GetGame(), GameStateType::Records, true);
			};
		
		MenuItem yesItem;
		setTextParameters(yesItem.text, L"Да", 24);
		yesItem.onPressCallback = [](MenuItem&) 
			{
				SwitchGameState(Application::Instance().GetGame(), GameStateType::None);
			};

		MenuItem noItem;
		setTextParameters(noItem.text, L"Нет", 24);
		noItem.onPressCallback = [&data](MenuItem&)
			{
				data.menu.GoBack();
			};

		MenuItem exitGame;
		setTextParameters(exitGame.text, L"Выйти из игры", 24);

		setTextParameters(exitGame.hintText, L"Вы уверены?", 48, sf::Color::Red);
		exitGame.childrenOrientation = Orientation::Horizontal;
		exitGame.childrenAlignment = Alignment::Middle;
		exitGame.childrenSpacing = 10.f;
		exitGame.childrens.push_back(yesItem);
		exitGame.childrens.push_back(noItem);

		MenuItem mainMenu;
		setTextParameters(mainMenu.hintText, L"Змейка", 48, sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(difficulty);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(records);
		mainMenu.childrens.push_back(exitGame);

		data.menu.Init(mainMenu);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, const sf::Event& event)
	{
		Game& game = Application::Instance().GetGame();
		
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				data.menu.GoBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (IsEnableOptions(game, GameOptions::Sound))
				{
					data.soundBtnHover.play();
				}
				data.menu.PressOnSelectedItem();
			}

			Orientation orientation = data.menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				data.menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				data.menu.SwitchToNextMenuItem();
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta)
	{
		Game& game = Application::Instance().GetGame();
		data.difficultyEasy.text.setString(L"Лёгкий: " + std::wstring(game.difficulty == DifficultyLevel::Easy ? L"Вкл" : L"Выкл"));
		data.difficultyNormal.text.setString(L"Нормальный: " + std::wstring(game.difficulty == DifficultyLevel::Normal ? L"Вкл" : L"Выкл"));
		data.difficultyHard.text.setString(L"Сложный: " + std::wstring(game.difficulty != DifficultyLevel::Hard ? L"Вкл" : L"Выкл"));
		data.difficultyInsane.text.setString(L"Безумный: " + std::wstring(game.difficulty != DifficultyLevel::Insane ? L"Вкл" : L"Выкл"));
		data.difficultyImpossible.text.setString(L"Невозможный: " + std::wstring(game.difficulty != DifficultyLevel::Impossible ? L"Вкл" : L"Выкл"));

		
		//bool isMusic = ((std::uint8_t)Application::Instance().GetGame().options & (std::uint8_t)GameOptions::Music);
		//data.optionsMusicItem.text.setString(L"Музыка: " + std::wstring(isMusic ? L"Вкл" : L"Выкл"));
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &data.menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		data.menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}