#include "core.h"
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

nc::Scene scene;
nc::ParticleSystem g_particleSystem;

float frametime;
float spawnTimer = 0;

bool Update(float dt)
{

	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[]{ nc::Color::purple, nc::Color::yellow, nc::Color::red };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create(nc::Vector2{x, y}, 0, 180, 30, color, 1.0f, 100, 200);
	}

	g_particleSystem.Update(dt);
	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());

	g_particleSystem.Draw(graphics);
	scene.Draw(graphics);
}

int main()
{
	nc::Player* player = new nc::Player;

	scene.Startup();
	g_particleSystem.Startup();

	player->Load("player.txt");
	scene.AddActor(player);

	for (int i = 0; i < 100; i++)
	{
		nc::Actor* enemy = new nc::Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<nc::Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50, 100));

		scene.AddActor(enemy);
	}
	

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	scene.Shutdown();
	g_particleSystem.Shutdown();
}
