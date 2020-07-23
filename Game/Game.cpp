#include "Game.h"
#include "Math/MathStuff.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

nc::ParticleSystem g_particleSystem;

void Game::Startup()
{
	m_scene.Startup();
	g_particleSystem.Startup();
	m_scene.SetGame(this);
	
}

void Game::Shutdown()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
}

bool Game::Update(float dt)
{
	m_frametime += dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE)) m_state = eState::START_GAME;
		break;
	case Game::eState::START_GAME:
	{
		nc::Player* player = new nc::Player;
		player->Load("player.txt");
		m_scene.AddActor(player);

		for (int i = 0; i < 10; i++)
		{
			nc::Actor* enemy = new nc::Enemy;
			enemy->Load("enemy.txt");
			dynamic_cast<nc::Enemy*>(enemy)->SetTarget(player);
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50, 100));

			m_scene.AddActor(enemy);
		}

		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
		m_scene.Update(dt);
		m_spawnTimer += dt;
		if (m_spawnTimer >= 3.0f)
		{
			m_spawnTimer = 0;

			nc::Enemy* enemy = new nc::Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<nc::Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			m_scene.AddActor(enemy);
		}
		break;
	case Game::eState::GAME_OVER:
		break;
	default:
		break;
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[]{ nc::Color::purple, nc::Color::yellow, nc::Color::red };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create(nc::Vector2{ x, y }, 0, 180, 30, color, 1.0f, 100, 200);
	}

	g_particleSystem.Update(dt);


	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	//graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
	//graphics.DrawString(10, 20, std::to_string(1.0f / m_frametime).c_str());

	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "VECTOROIDS");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
	{
		m_scene.Draw(graphics);
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 0, "Score");
		graphics.DrawString(700, 10, std::to_string(m_score).c_str());
		break;
	}
	case Game::eState::GAME_OVER:
		graphics.SetColor(nc::Color::yellow);
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}
}
