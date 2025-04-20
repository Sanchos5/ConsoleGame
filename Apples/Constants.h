#pragma once

#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.0f; //Pixels per second
	const float PLAYER_SIZE = 20.0f;
	const float ACCELERATION = 50.0f;

	const float APPLE_SIZE = 20.0f;
	//const int NUM_APPLES = 10;
	//int numApple = 15;
	

	const float ROCK_SIZE = 20.0f;
	const int NUM_ROCKS = 10;

	const float FINISHED_LENGTH = 3.0f;

	//Game mode
	const int MODE_FINITE_APPLES = 1 << 0; // 0001
	const int MODE_INFINITE_APPLES = 1 << 1; // 0010
	const int MODE_ACCELERATED_PLAYER = 1 << 2; // 0100
	const int MODE_NO_ACCELERATION = 1 << 3; // 1000
}