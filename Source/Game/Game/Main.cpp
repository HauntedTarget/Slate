#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
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

	g_renderer.Initialize();

	g_renderer.CreateWindow("SlateEngine", 800, 600);

	g_inputSystem.Initialize();

	Model model;
	model.Load("player.txt");

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		vec2 pos(random((float)bls::g_renderer.GetWidth()), random((float)g_renderer.GetHeight()));
		vec2 vel(randomf(0.05f, 0.5f), 0.0f);

		stars.push_back(Star(pos, vel));
	}


	Player player{200, (float)DegreesToRadians(180), { {400,300}, 0, 3 }, model };

	vector<Enemy> enemies;
	for (int i = 0; i < 10; i++)
	{
		Enemy enemy{300, (float)DegreesToRadians(180), { {400,300}, randomf(TwoPi), 6}, model};
		enemies.push_back(enemy);

	}



	//Game Loop
	bool quit = false;
	while (!quit)
	{
		//Update Engine
		g_time.Tick();

		g_inputSystem.Update();

		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//Update Game
		player.Update(g_time.GetDeltaTime());
		for (auto& enemy : enemies)
		{
			enemy.Update(g_time.GetDeltaTime());
		}
		

		g_renderer.SetColor(0, 0, 0, 255);
		g_renderer.BeginFrame();

		for (auto& star : stars)
		{
			star.Update();

			if (star.m_pos.x > g_renderer.GetWidth()) {
				star.m_pos.x = 0;
			}
			if (star.m_pos.y > g_renderer.GetHeight()) {
				star.m_pos.y = 0;
			}

			g_renderer.SetColor(random(256), random(256), random(256), 255);
			g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		g_renderer.SetColor(255, 255, 255, 255);
		player.Draw(g_renderer);

		g_renderer.SetColor(255, 0, 0, 255);
		for (auto& enemy : enemies)
		{
			enemy.Draw(g_renderer);
		}

		g_renderer.EndFrame();
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