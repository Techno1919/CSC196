#include "core.h"
#include "Math/MathStuff.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

std::list<nc::Actor*> actors;
float frametime;
float spawnTimer = 0;

template <typename T>
nc::Actor* GetActor()
{
	nc::Actor* result{nullptr};

	for (nc::Actor* actor : actors)
	{
		result = dynamic_cast<T*>(actor);
		if (result) break;
	}

	return result;
}

template <typename T>
std::vector<nc::Actor*> GetActors()
{
	std::vector<nc::Actor*> results;

	for (nc::Actor* actor : actors)
	{
		T* result = dynamic_cast<T*>(actor);
		if (result)
		{
			results.push_back(result);
		}
	}

	return results;
}

bool Update(float dt)
{

	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	if (Core::Input::IsPressed(VK_SPACE))
	{
		auto removeActors = GetActors<nc::Enemy>();
		for (auto actor : removeActors)
		{
			auto iter = std::find(actors.begin(), actors.end(), actor);
			delete* iter;
			actors.erase(iter);
		}
	}

	spawnTimer += dt;
	if (spawnTimer >= 3.0f)
	{
		spawnTimer = 0;


		// add enemy to scene
		nc::Actor* actor = new nc::Enemy;
		actor->Load("enemy.txt");
		dynamic_cast<nc::Enemy*>(actor)->SetTarget(GetActor<nc::Player>());
		actor->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<nc::Enemy*>(actor)->SetThrust(nc::random(50, 100));

		actors.push_back(actor);
	}

	for (nc::Actor* actor : actors)
	{
		actor->Update(dt);
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());

	for (nc::Actor* actor : actors)
	{
		actor->Draw(graphics);
	}
}

int main()
{
	nc::Player* player = new nc::Player;

	player->Load("player.txt");
	actors.push_back(player);

	for (int i = 0; i < 100; i++)
	{
		nc::Actor* enemy = new nc::Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<nc::Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50, 100));

		actors.push_back(enemy);
	}
	

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}


