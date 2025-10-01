#include "pch.h"
#include "AttackComponent.h"

namespace MyEngine
{
	AttackComponent::AttackComponent(GameObject* gameObject, float attackPower)
		: Component(gameObject), attackPower(attackPower)
	{
	}

	void AttackComponent::Update(float deltaTime)
	{
	}

	void AttackComponent::Render()
	{
	}

	void AttackComponent::SetAttackPower(float newAttackPower)
	{
		attackPower = newAttackPower;
	}

	void AttackComponent::Attack(GameObject* target)
	{
		if (!target)
		{
			return;
		}

		auto targetStatsComponent = target->GetComponent<StatsComponent>();
		if (targetStatsComponent)
		{
			float damage = attackPower;
			targetStatsComponent->TakeDamage(damage);
		}
	}
}