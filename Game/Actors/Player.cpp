#include "Player.h"
#include "Projectile.h"
#include "Math/MathStuff.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
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
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;
		Projectile* projectile = new Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);

	}


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


	if (force.Length() > 0)
	{
		g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::blue, 1.0f, 100, 200);
	}


	m_transform.Update();

}

