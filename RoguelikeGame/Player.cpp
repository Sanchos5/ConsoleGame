#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <AudioComponent.h>

namespace RoguelikeGame
{
	Player::Player(const MyEngine::Vector2Df& position)
	{
		gameObject = MyEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto transform = gameObject->GetComponent<MyEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<MyEngine::SpriteRendererComponent>();
		renderer->SetTexture(*MyEngine::ResourceSystem::Instance()->GetTextureMapElementShared("player", 0));
		renderer->SetPixelSize(100, 100);

		auto playerCamera = gameObject->AddComponent<MyEngine::CameraComponent>();
		playerCamera->SetWindow(&MyEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<MyEngine::InputComponent>();

		/*auto transform = gameObject->GetComponent<MyEngine::TransformComponent>();
		transform->RotateBy(90.f);
		transform->MoveBy({ 1.f, 0.f });

		auto test = MyEngine::GameWorld::Instance()->CreateGameObject();
		auto testTransform = test->GetComponent<MyEngine::TransformComponent>();
		testTransform->SetParent(transform);

		transform->RotateBy(-90.f);
		transform->Print();
		testTransform->Print();*/

		auto rigidbody = gameObject->AddComponent<MyEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collider = gameObject->AddComponent<MyEngine::SpriteColliderComponent>();

		//auto music = gameObject->AddComponent<MyEngine::AudioComponent>();
		//music->SetAudio(*MyEngine::ResourceSystem::Instance()->GetSound("music"));
		//music->Play();
		//music->SetLoop(true);

	}

	MyEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}