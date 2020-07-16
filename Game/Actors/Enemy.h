#pragma once
#pragma once
#include "Object/Actor.h"

namespace nc
{
	class Enemy : public nc::Actor
	{
	public:
		Enemy() = default;
		virtual ~Enemy() {};

		virtual bool Load(const std::string& filename) override;
		virtual void Update(float dt) override;

		void SetThrust(float thrust) { m_thrust = thrust; }
		void SetTarget(Actor* actor) { m_target = actor; }

	protected:
		float m_thrust{ 0.0f };
		Actor* m_target{ nullptr };

	};

}

