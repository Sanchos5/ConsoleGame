#pragma once
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include <Pawn.h>

namespace RoguelikeGame
{
	class Player : public MyEngine::Pawn
	{
		public:

			Player(const MyEngine::Vector2Df& position);
			MyEngine::GameObject* GetGameObject();

			void Update(float deltaTime) override;

		private:

			MyEngine::GameObject* gameObject;
	};
}

