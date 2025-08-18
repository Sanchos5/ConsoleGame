#pragma once

#include <string>

namespace SnakeGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const float INITIAL_SPEED = 50.0f; //Pixels per second
	const float PLAYER_SIZE = 20.0f;
	const float ACCELERATION = 50.0f;

	const float APPLE_SIZE = 20.0f;
	//const int NUM_APPLES = 10;
	//int numApple = 15;
	

	const float ROCK_SIZE = 20.0f;
	const int NUM_ROCKS = 10;

	const float FINISHED_LENGTH = 3.0f;

	const int MAX_RECORDS_TABLE_SIZE = 6;
}