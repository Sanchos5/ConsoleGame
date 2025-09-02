#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball : public GameObject
	{
		public:

			void Init() override;
			void Update(float deltaTime) override;

			void ReboundFromPlatform();

		private:

			sf::Vector2f direction;
	};
}

