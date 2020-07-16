// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

const size_t NUM_POINTS = 40;

//nc::Actor player;
//nc::Actor enemy;

nc::Player player;
nc::Enemy enemy;

float thrust = 300;
nc::Vector2 velocity;

float t{ 0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt)
{
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;
	
	t = (t + dt * 0.5f);

	frametime = dt;
	roundTime += dt;
	//if (roundTime >= 5) gameOver = true;

	if (gameOver) dt /= 2;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	player.Update(dt);
	enemy.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f;

	nc::Color c = nc::Lerp(nc::Color{ 0, 0, 1 }, nc::Color{ 1, 0, 0 }, v);
	graphics.SetColor(c);

	nc::Vector2 p = nc::Lerp(nc::Vector2{ 400, 300 }, nc::Vector2{ 0 , 0 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");

	if (gameOver) graphics.DrawString(400, 300, "Game Over");


	player.Draw(graphics);
	enemy.Draw(graphics);

}

int main()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 << std::endl;
	prevTime = GetTickCount();

	player.Load("player.txt");
	enemy.Load("enemy.txt");
	enemy.SetTarget(&player);

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}


