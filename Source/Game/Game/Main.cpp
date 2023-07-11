#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include <iostream>
#include <vector>
#include <thread>

using namespace bls;
using namespace std;


class Star
{
public:
	Star(const vec2& pos, const vec2& vel):
		m_pos{pos},
		m_vel{vel}
	{}

	void Update()
	{
		m_pos += m_vel;
	}

public:
	vec2 m_pos;
	vec2 m_vel;
};

int main(int argc, char* argv[])
{
	seedRandom((unsigned int)time(nullptr));

	setFilePath("assets");

	Renderer renderer;

	renderer.Initialize();

	renderer.CreateWindow("SlateEngine", 800, 600);

	InputSystem inputSystem;
	inputSystem.Initialize();

	Model model;
	model.Load("player.txt");

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		vec2 pos(random(renderer.GetWidth()), random(renderer.GetHeight()));
		vec2 vel(randomf(0.05f, 0.5f), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	vec2 position{ 400,300 };
	float speed = 200;

	bool quit = false;
	while (!quit)
	{
		g_time.Tick();

		inputSystem.Update();

		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		vec2 direction;

		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		position += direction * speed * g_time.GetDeltaTime();

		renderer.SetColor(0, 0, 0, 255);
		renderer.BeginFrame();

		for (auto& star : stars)
		{
			star.Update();

			if (star.m_pos.x > renderer.GetWidth()) {
				star.m_pos.x = 0;
			}
			if (star.m_pos.y > renderer.GetHeight()) {
				star.m_pos.y = 0;
			}

			renderer.SetColor(random(256), random(256), random(256), 255);
			renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		renderer.SetColor(255, 255, 255, 255);
		model.Draw(renderer, position, 6.5);

		renderer.EndFrame();
	}

	/*g_memoryTracker.DisplayInfo();

	int* p = new int;
	g_memoryTracker.DisplayInfo();

	delete p;
	g_memoryTracker.DisplayInfo();

	Time timer;
	for (int i = 0; i < 1000000; i++) {}
	cout << timer.GetElapsedNanoseconds() << endl;*/

	//Time (Unneeded)
	/*
	auto i = true;
	auto start = high_resolution_clock::now();

	for (int i = 0; i < 100000; i++) {}

	auto end = high_resolution_clock::now();

	cout << duration_cast<microseconds>(end - start).count();*/

	//Paths
	/*cout << "Hello World\n";

	cout << getFilePath() << endl;

	setFilePath("Assets");
	cout << getFilePath() << endl;

	size_t size;
	getFileSize("Game.txt", size);
	cout << size << endl;

	std::string s;
	readFile("Game.txt", s);
	cout << s << endl;

	seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 3; i++) {
		cout << random(10, 20) << endl;
	}*/

	return 0;
}