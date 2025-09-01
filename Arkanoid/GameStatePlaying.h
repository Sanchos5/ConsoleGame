#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Ball.h"
#include "Platform.h"

namespace ArkanoidGame
{
	class GameStatePlayingData
	{
		public:

			void Init();
			void HandleWindowEvent(const sf::Event& event);
			void Update(float deltaTime);
			void Draw(sf::RenderWindow& window);

		private:

			//Resources
			sf::Texture platformTexture;
			sf::Texture ballTexture;

			//sf::SoundBuffer soundAppleEatBuffer;
			//sf::SoundBuffer soundDeathBuffer;
			//sf::SoundBuffer soundBackgroundBuffer;

			//Game data
			Platform platform;
			Ball ball;

			// UI data
			sf::Font font;
			sf::Text scoreText;
			sf::Text inputHintText;
			sf::RectangleShape background;

			//Sound
			//sf::Sound soundAppleEat;
			//sf::Sound soundDeath;
			//sf::Sound soundBackground;
	};
}

