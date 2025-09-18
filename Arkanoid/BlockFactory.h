#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Block;

	class BlockFactory
	{
		public:

			virtual ~BlockFactory() = default;
			virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) = 0;
			int GetCreatedBreackableBlocksCount();
			void ClearCounter();

		protected:

			int createdBreackableBlocksCount = 0;
	};

	class SimpleBlockFactory final : public BlockFactory
	{
		public:

			~SimpleBlockFactory() override = default;
			std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
	};

	class ThreeHitBlockFactory final : public BlockFactory
	{
		public:

			~ThreeHitBlockFactory() override = default;
			std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
	};

	class UnbreackableBlockFactory final : public BlockFactory
	{
		public:

			~UnbreackableBlockFactory() override = default;
			std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
	};
}
