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
				Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
			};

		const bool isEasy = game.IsEnableDifficultyLevel(DifficultyLevel::Easy);
		MenuItem difficultyEasy;
		setTextParameters(difficultyEasy.text, L"Лёгкий: " + std::wstring(isEasy ? L"Вкл" : L"Выкл"), 24);
		difficultyEasy.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newEasy = !game.IsEnableDifficultyLevel(DifficultyLevel::Easy);
				game.SetDifficultyLevel(DifficultyLevel::Easy, newEasy);
				item.text.setString(L"Лёгкий: " + std::wstring(newEasy ? L"Вкл" : L"Выкл"));
			};

		const bool isNormal = game.IsEnableDifficultyLevel(DifficultyLevel::Normal);
		MenuItem difficultyNormal;
		setTextParameters(difficultyNormal.text, L"Нормальный: " + std::wstring(isNormal ? L"Вкл" : L"Выкл"), 24);
		difficultyNormal.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newNormal = !game.IsEnableDifficultyLevel(DifficultyLevel::Normal);
				game.SetDifficultyLevel(DifficultyLevel::Normal, newNormal);
				item.text.setString(L"Нормальный: " + std::wstring(newNormal ? L"Вкл" : L"Выкл"));
			};


		const bool isHard = game.IsEnableDifficultyLevel(DifficultyLevel::Hard);
		MenuItem difficultyHard;
		setTextParameters(difficultyHard.text, L"Сложный: " + std::wstring(isHard ? L"Вкл" : L"Выкл"), 24);
		difficultyHard.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newHard = !game.IsEnableDifficultyLevel(DifficultyLevel::Hard);
				game.SetDifficultyLevel(DifficultyLevel::Hard, newHard);
				item.text.setString(L"Сложный: " + std::wstring(newHard ? L"Вкл" : L"Выкл"));
			};

		const bool isInsane = game.IsEnableDifficultyLevel(DifficultyLevel::Insane);
		MenuItem difficultyInsane;
		setTextParameters(difficultyInsane.text, L"Безумный: " + std::wstring(isInsane ? L"Вкл" : L"Выкл"), 24);
		difficultyInsane.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newInsane = !game.IsEnableDifficultyLevel(DifficultyLevel::Insane);
				game.SetDifficultyLevel(DifficultyLevel::Insane, newInsane);
				item.text.setString(L"Безумный: " + std::wstring(newInsane ? L"Вкл" : L"Выкл"));
			};

		const bool isImpossible = game.IsEnableDifficultyLevel(DifficultyLevel::Impossible);
		MenuItem difficultyImpossible;
		setTextParameters(difficultyImpossible.text, L"Невозможный: " + std::wstring(isImpossible ? L"Вкл" : L"Выкл"), 24);
		difficultyImpossible.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newImpossible = !game.IsEnableDifficultyLevel(DifficultyLevel::Impossible);
				game.SetDifficultyLevel(DifficultyLevel::Impossible, newImpossible);
				item.text.setString(L"Невозможный: " + std::wstring(newImpossible ? L"Вкл" : L"Выкл"));
			};

		MenuItem difficulty;
		setTextParameters(difficulty.text, L"Уровень сложности", 24);
		setTextParameters(difficulty.hintText, L"Выберите уровень сложности", 48, sf::Color::Red);
		difficulty.childrenOrientation = Orientation::Vertical;
		difficulty.childrenAlignment = Alignment::Middle;
		difficulty.childrenSpacing = 10.f;
		difficulty.childrens.push_back(difficultyEasy);
		difficulty.childrens.push_back(difficultyNormal);
		difficulty.childrens.push_back(difficultyHard);
		difficulty.childrens.push_back(difficultyInsane);
		difficulty.childrens.push_back(difficultyImpossible);
		
		const bool isSound = game.IsEnableOptions(GameOptions::Sound);
		MenuItem optionsSound;
		setTextParameters(optionsSound.text, L"Звук: " + std::wstring(isSound ? L"Вкл" : L"Выкл"), 24);
		optionsSound.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newSound = !game.IsEnableOptions(GameOptions::Sound);
				game.SetOption(GameOptions::Sound, newSound);
				item.text.setString(L"Звук: " + std::wstring(newSound ? L"Вкл" : L"Выкл"));
			};

		const bool isMusic = game.IsEnableOptions(GameOptions::Music);
		MenuItem optionsMusic;
		setTextParameters(optionsMusic.text, L"Музыка: " + std::wstring(isMusic ? L"Вкл" : L"Выкл"), 24);
		optionsMusic.onPressCallback = [](MenuItem& item)
			{
				Game& game = Application::Instance().GetGame();
				bool newMusic = !game.IsEnableOptions(GameOptions::Music);
				game.SetOption(GameOptions::Music, newMusic);
				item.text.setString(L"Музыка: " + std::wstring(newMusic ? L"Вкл" : L"Выкл"));
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
				Application::Instance().GetGame().PushState(GameStateType::Records, true);
			};
		
		MenuItem yesItem;
		setTextParameters(yesItem.text, L"Да", 24);
		yesItem.onPressCallback = [](MenuItem&) 
			{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::None);
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
				if (game.IsEnableOptions(GameOptions::Sound))
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