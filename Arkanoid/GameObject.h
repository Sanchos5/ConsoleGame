#pragma once
#include "GameObject.h"
#include "Sprite.h"

namespace ArkanoidGame
{
	class GameObject
	{
		public:

			void Draw(sf::RenderWindow& window);

			const sf::Vector2f& GetPosition() const { return sprite.getPosition(); }
			const sf::FloatRect& GetRect() const { return sprite.getGlobalBounds(); }

		protected:
			sf::Sprite sprite;
			sf::Texture texture;
	};
}



