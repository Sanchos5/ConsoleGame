#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Collision.h"

namespace ArkanoidGame
{
	class Ball;

	class Platform : public GameObject, public Collision
	{
		public:

			Platform(const sf::Vector2f& position);

			void Update(float deltaTime) override;

			bool GetCollision(std::shared_ptr<Collision> collision) const override;
			void OnHit() override {}
			bool CheckCollision(std::shared_ptr<Collision> collision) override;

		private:
			void Move(float speed);
	};
}

