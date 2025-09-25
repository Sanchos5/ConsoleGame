// Arkanoid.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include <windows.h>

using namespace RoguelikeGame;

int main()
{

	//Выделяем консоль и перенаправляем вывод
	if(AllocConsole())
	{
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout); //Перенаправляем stdout в консоль
		freopen_s(&fp, "CONOUT$", "w", stderr); //Перенаправляем stderr в консоль
	}
	else
	{
		std::cerr << "Не удалось выделить консоль." << std::endl;
	}

	MyEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike"));

	MyEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	MyEngine::Engine::Instance()->Run();

	return 0;
}