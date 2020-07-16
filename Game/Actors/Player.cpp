#include "Player.h"
#include "Math/MathStuff.h"
#include <fstream>

bool nc::Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		// load the base actor members
		Actor::Load(stream);

		// stream into thrust
		stream >> m_thrust;
		// stream into rotation rate
		stream >> rotationRate;

		stream.close();
	}

	return success;

}

void nc::Player::Update(float dt)
{
	nc::Vector2 force{ 0,0 };
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);
	m_velocity = m_velocity + force * dt;
	m_velocity *= 0.99f;

	m_transform.position += (m_velocity * dt);

	if (Core::Input::IsPressed('A')) { m_transform.angle -= (dt * nc::DegreesToRadians(rotationRate)); }
	if (Core::Input::IsPressed('D')) { m_transform.angle += (dt * nc::DegreesToRadians(rotationRate)); }

	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 800;
	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;

	m_transform.Update();

}

