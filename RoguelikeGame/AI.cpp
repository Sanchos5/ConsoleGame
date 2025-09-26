#include "AI.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
//#include "MovementComponent.h"

#include <FollowComponent.h>


namespace RoguelikeGame
{
	AI::AI(const MyEngine::Vector2Df& position, MyEngine::GameObject* player)
	{
		gameObject = MyEngine::GameWorld::Instance()->CreateGameObject("AI");
		auto transform = gameObject->GetComponent<MyEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<MyEngine::SpriteRendererComponent>();
		renderer->SetTexture(*MyEngine::ResourceSystem::Instance()->GetTextureMapElementShared("AI", 0));
		renderer->SetPixelSize(100, 100);

		auto follower = gameObject->AddComponent<MyEngine::FollowComponent>();
		follower->SetTarget(player);
		follower->SetSpeed(120.0f);

		auto rigidbody = gameObject->AddComponent<MyEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collideer = gameObject->AddComponent<MyEngine::SpriteColliderComponent>();
	}

	MyEngine::GameObject* AI::GetGameObject()
	{
		return gameObject;
	}
}