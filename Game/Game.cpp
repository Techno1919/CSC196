// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/MathStuff.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <vector>
#include <string>

const size_t NUM_POINTS = 40;
float speed = 300;

std::vector<nc::Vector2> points = { { 0, -3 }, { 3, 3 }, { -1, 3 }, {4, -3}, {0 , -3} };
nc::Color color{0, 1, 1};
nc::Shape shape;
//nc::Shape shape{ points, color };

nc::Transform transform{ {400.0f, 300.0f}, 4.0f, 0.0f };

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
	


	frametime = dt;
	roundTime += dt;
	if (roundTime >= 5) gameOver = true;

	if (gameOver) dt /= 2;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	//nc::Vector2 target = nc::Vector2{ x, y };
	//nc::Vector2 direction = target - position;
	//direction.Normalize();

	nc::Vector2 force{ 0,0 };
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed * dt; }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, transform.angle);
	transform.position += direction;

	if (Core::Input::IsPressed('A')) {transform.angle -= (dt * 3.0f);}
	if (Core::Input::IsPressed('D')) {transform.angle += (dt * 3.0f);}

	/*if (Core::Input::IsPressed('A')) position += nc::Vector2::left * speed * dt;
	if (Core::Input::IsPressed('D')) position += nc::Vector2::right * speed * dt;
	if (Core::Input::IsPressed('W')) position += nc::Vector2::up * speed * dt;
	if (Core::Input::IsPressed('S')) position += nc::Vector2::down * speed * dt;
	*/
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	shape.Draw(graphics, transform);

}

int main()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 << std::endl;
	prevTime = GetTickCount();

	shape.Load("shape.txt");

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}


