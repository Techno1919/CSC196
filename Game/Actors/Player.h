#pragma once
#include "Object/Actor.h"

namespace nc
{
	class Player : public nc::Actor
	{
	public:
		virtual bool Load(const std::string& filename) override;

		virtual eType GetType() { return eType::PLAYER; }

		virtual void Update(float dt) override;
		
		virtual void OnCollision(Actor* actor);

	protected:
		float m_thrust{ 300 };
		float rotationRate{ 360.0f };
		float m_fireRate{ 0.25f };
		float m_fireTimer{ 0.0f };
		nc::Vector2 m_velocity{};
	};
}
