#include "GameState.h"
#include "GameStateMainMenu.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateExitDialog.h"
#include "GameRecords.h"
#include <assert.h>

namespace ArkanoidGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible)
		: type(type)
		, isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)data);
			break;
		}
		case GameStateType::Playing:
		{
			data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)data);
			break;
		}
		case GameStateType::GameOver:
		{
			data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)data);
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = new GameStateExitDialogData();
			InitGameStateExitDialog(*(GameStateExitDialogData*)data);
			break;
		}
		case GameStateType::Records:
		{
			data = new GameStateRecordsData();
			InitGameRecord(*(GameStateRecordsData*)data);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	GameState::~GameState()
	{
		if (data) {
			switch (type)
			{
			case GameStateType::MainMenu:
			{
				ShutdownGameStateMainMenu(*(GameStateMainMenuData*)data);
				delete ((GameStateMainMenuData*)data);
				break;
			}
			case GameStateType::Playing:
			{
				ShutdownGameStatePlaying(*(GameStatePlayingData*)data);
				delete ((GameStatePlayingData*)data);
				break;
			}
			case GameStateType::GameOver:
			{
				ShutdownGameStateGameOver(*(GameStateGameOverData*)data);
				delete ((GameStateGameOverData*)data);
				break;
			}
			case GameStateType::ExitDialog:
			{
				ShutdownGameStateExitDialog(*(GameStateExitDialogData*)data);
				delete ((GameStateExitDialogData*)data);
				break;
			}
			case GameStateType::Records:
			{
				ShutdownGameStateRecords(*(GameStateRecordsData*)data);
				delete ((GameStateRecordsData*)data);
				break;
			}
			default:
				assert(false); // We want to know if we forgot to implement new game state
				break;
			}

			data = nullptr;
		}
	}

	void GameState::Update(float deltaTime)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)data, deltaTime);
			break;
		}
		case GameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)data, deltaTime);
			break;
		}
		case GameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)data, deltaTime);
			break;
		}
		case GameStateType::ExitDialog:
		{
			UpdateGameStateExitDialog(*(GameStateExitDialogData*)data, deltaTime);
			break;
		}
		case GameStateType::Records:
		{
			UpdateGameStateRecords(*(GameStateRecordsData*)data, deltaTime);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)data, window);
			break;
		}
		case GameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)data, window);
			break;
		}
		case GameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)data, window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			DrawGameStateExitDialog(*(GameStateExitDialogData*)data, window);
			break;
		}
		case GameStateType::Records:
		{
			DrawGameStateRecords(*(GameStateRecordsData*)data, window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)data, event);
			break;
		}
		case GameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)data, event);
			break;
		}
		case GameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)data, event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			HandleGameStateExitDialogWindowEvent(*(GameStateExitDialogData*)data, event);
			break;
		}
		case GameStateType::Records:
		{
			HandleGameStateRecordsWindowEvent(*(GameStateRecordsData*)data, event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void* GameState::CopyData(const GameState& state) const
	{
		void* data = nullptr;
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenuData();
			*((GameStateMainMenuData*)data) = *(GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			data = new GameStatePlayingData();
			*((GameStatePlayingData*)data) = *(GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			data = new GameStateGameOverData();
			*((GameStateGameOverData*)data) = *(GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = new GameStateExitDialogData();
			*((GameStateExitDialogData*)data) = *(GameStateExitDialogData*)state.data;
			break;
		}
		case GameStateType::Records:
		{
			data = new GameStateRecordsData();
			*((GameStateRecordsData*)data) = *(GameStateRecordsData*)state.data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
		return data;
	}
}