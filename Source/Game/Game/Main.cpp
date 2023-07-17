//Included Files (Always needed)
#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include <thread>

//Used Namespaces (Shave off little bits of code)
using namespace bls;
using namespace std;

//Star Feild Function
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

//Main Function
int main(int argc, char* argv[])
{
	//Sets "Random" Seed
	seedRandom((unsigned int)time(nullptr));

	//Init Systems
	g_audioSystem.Initialize();
	g_renderer.Initialize();
	g_inputSystem.Initialize();

	//Create Game Window
	g_renderer.CreateWindow("SlateEngine", 800, 600);

	//Selects Asset Filepath
	setFilePath("assets");

	//Init Assets
	g_audioSystem.AddAudio("death", "explode.wav");
	g_audioSystem.AddAudio("shoot", "lazer.wav");

	//Load Player Model
	Model model;
	model.Load("player.txt");

	//Star Field Creation
	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		vec2 pos(random((float)bls::g_renderer.GetWidth()), random((float)g_renderer.GetHeight()));
		vec2 vel(randomf(0.05f, 0.5f), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	Scene scene;

	//Player Creation
	scene.Add(new Player{ 200, (float)DegreesToRadians(180), { {400,300}, 0, 3 }, model });

	//Enemy Array Creation
	
	vector<Enemy> enemies;
	for (int i = 0; i < 5; i++)
	{
		Enemy* enemy = new Enemy{300, (float)DegreesToRadians(180), { {400,300}, randomf(TwoPi), 6}, model};
		scene.Add(enemy);

	}

	//Game Loop
	bool quit = false;
	while (!quit)
	{
		//Update Audio System
		g_audioSystem.Update();

		//Update Engine
		g_time.Tick();

		g_inputSystem.Update();

		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//Update Game
		scene.Update(g_time.GetDeltaTime());
		
		//Frame Init
		g_renderer.SetColor(0, 0, 0, 255);
		g_renderer.BeginFrame();

		//Star Drawer
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

		//Player Drawer
		g_renderer.SetColor(255, 255, 255, 255);
		scene.Draw(g_renderer);

		//Enemy Drawer (Re-add With Varients)
		//g_renderer.SetColor(255, 0, 0, 255);
		//scene.Draw(g_renderer);

		//End of Frame
		g_renderer.EndFrame();
	}

	//End of File
	return 0;
}