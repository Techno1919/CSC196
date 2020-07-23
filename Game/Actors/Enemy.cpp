#include "Enemy.h"
#include "Math/MathStuff.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
#include <fstream>

bool nc::Enemy::Load(const std::string& filename)
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

        stream.close();
    }

    return success;

}

void nc::Enemy::Update(float dt)
{
    //enemy
    nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
    nc::Vector2 eVelocity = direction.Normalized() * 0;// m_thrust;
    m_transform.position += eVelocity * dt;
    m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);

    m_transform.Update();
}

void nc::Enemy::OnCollision(Actor* actor)
{
    if (actor->GetType() == eType::PROJECTILE)
    {
        m_destroy = true;

        // set game score
        m_scene->GetGame()->AddPoints(100);

        nc::Color colors[]{ nc::Color::purple, nc::Color::yellow, nc::Color::red };
        nc::Color color = colors[rand() % 3];

        g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1.0f, 100, 200);
    }
}
