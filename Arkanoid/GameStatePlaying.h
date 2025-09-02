#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Ball.h"
#include "Platform.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class GameStatePlayingData : public GameStateData
	{
		public:

			void HandleWindowEvent(const sf::Event& event) override;
			void Init() override;
			void Update(float deltaTime) override;
			void Draw(sf::RenderWindow& window) override;

		private:

			//Resources
			sf::Texture platformTexture;
			sf::Texture ballTexture;

			//sf::SoundBuffer soundAppleEatBuffer;
			//sf::SoundBuffer soundDeathBuffer;
			//sf::SoundBuffer soundBackgroundBuffer;

			//Game data
			std::vector<std::shared_ptr<GameObject>> gameObjects;

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

