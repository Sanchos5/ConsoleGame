#pragma once
#include "GameObject.h"
#include "Ball.h"
#include "Collision.h"
#include "DelayedAction.h"
#include "IObserver.h"


namespace ArkanoidGame
{
	class Block : public GameObject, public Collision, public IObservable
	{
		public:

			Block(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
			virtual ~Block();
			bool GetCollision(std::shared_ptr<Collision> collisionObject) const override;
			void Update(float timeDelta) override;
			bool IsBroken();

			bool isHit = false;

			int ScoreValue = 0;
		protected:

			void OnHit();
			int hitCount = 1;
			
	};

	class SmoothDestroyableBlock : public Block, public DelayedAction
	{
		public:

			SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
			~SmoothDestroyableBlock() = default;
			void Update(float deltaTime) override;
			bool GetCollision(std::shared_ptr<Collision> collisionObject) const override;

		protected:

			void OnHit() override;
			void FinalAction() override;
			void EachTickAction(float deltaTime) override;
			sf::Color color;
	};

	class UnbreackableBlock : public Block
	{
		public:

			UnbreackableBlock(const sf::Vector2f& position);
			void OnHit() override;
			void Update(float) 
			{
				int i = 0;
				++i;
			};
	};

	class ThreeHitBlock : public SmoothDestroyableBlock
	{
		public:

			ThreeHitBlock(const sf::Vector2f& position);
			
		protected:

			void OnHit() override;
			void StageChange();
	};
}


