#pragma once
#include "Object/Actor.h"

namespace nc
{
	class Player : public nc::Actor
	{
	public:
		virtual bool Load(const std::string& filename) override;

		virtual void Update(float dt) override;

	protected:
		float m_thrust{ 300 };
		float rotationRate{};
		nc::Vector2 m_velocity{};
	};
}
