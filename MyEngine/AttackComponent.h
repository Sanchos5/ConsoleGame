#pragma once
#include "Component.h"
#include "GameObject.h"
#include "StatsComponent.h"

namespace MyEngine
{
	class AttackComponent : public Component
	{
		public:

			AttackComponent(GameObject* gameObject, float attackPower);

			void Update(float deltaTime) override;
			void Render() override;

			float GetAttackPower() const { return attackPower; }

			void SetAttackPower(float newAttackPower);

			void Attack(GameObject* target);

		private:

			float attackPower;
	};
}


