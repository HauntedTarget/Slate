	//Included Files (Always needed)
#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
	//Included Libs (Always needed)
#include <iostream>
#include <thread>
#include <vector>

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
	MemoryTracker::Initialize();

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

		// Init Font
	shared_ptr<Font> font = make_shared<Font>("Arcade.ttf", 24);
	
		//Create Text Object
	unique_ptr<Text> text = make_unique<Text>(font);
	text->Create(g_renderer, "AHHHHHHHHHHHHHHH", Color{ 0.5, 1, 0, 1 });

		//Load Player Model
	Model model;
	model.Load("player.txt");

		//Star Field Creation
	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		vec2 pos(random((float)bls::g_renderer.GetWidth()), random((float)bls::g_renderer.GetHeight()));
		vec2 vel(randomf(0.05f, 0.5f), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	Scene scene;

		//Player Creation
	scene.Add(make_unique<Player>(200.0f, (float)DegreesToRadians(180), Transform( (400,300), 0, 3 ), model ));

		//Enemy Array Creation
	vector<Enemy> enemies;
	for (int i = 0; i < 5; i++)
	{
		unique_ptr<Enemy> enemy = make_unique<Enemy>(300.0f, (float)DegreesToRadians(180), Transform((random((float)g_renderer.GetWidth()), random((float)g_renderer.GetHeight())), randomf(360), 5), model);
		scene.Add(move(enemy));

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

		//Text Drawer
		text->Draw(g_renderer, 400, 300);

			//End of Frame
		g_renderer.EndFrame();
	}

		//End of File
	return 0;
}