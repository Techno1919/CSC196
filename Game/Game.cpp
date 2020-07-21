#include "core.h"
#include "Math/MathStuff.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"
#include "Object/Scene.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

nc::Scene scene;
float frametime;
float spawnTimer = 0;

bool Update(float dt)
{

	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());

	scene.Draw(graphics);
}

int main()
{
	nc::Player* player = new nc::Player;

	scene.Startup();
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
}
