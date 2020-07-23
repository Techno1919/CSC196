#pragma once
#pragma once
#include "Object/Actor.h"

namespace nc
{
	class Projectile : public nc::Actor
	{
	public:
		Projectile() = default;
		virtual ~Projectile() {};

		virtual eType GetType() { return eType::PROJECTILE; }

		virtual bool Load(const std::string& filename) override;
		virtual void Update(float dt) override;

		virtual void OnCollision(Actor* actor)
		{
			if (actor->GetType() == eType::ENEMY)
			{
				m_destroy = true;
			}
		}

		void SetThrust(float thrust) { m_thrust = thrust; }

	protected:
		float m_thrust{ 0.0f };
		float m_lifetime{ 3 };
	};

}

