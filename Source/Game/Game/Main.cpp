	//Included Files (Always needed)
#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "FrameLastGame.h"
#include "Framework/Emitter.h"
#include "Framework/Scene.h"
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
		//Start of Game Info Log
	INFO_LOG;

		//MemTracker Init
	MemoryTracker::Initialize();

		//Sets "Random" Seed
	seedRandom((unsigned int)time(nullptr));

		//Init Systems
	g_audioSystem.Initialize();
	g_renderer.Initialize();
	g_inputSystem.Initialize();

		//Selects Asset Filepath
	setFilePath("assets");

		//Create Game Window
	g_renderer.CreateWindow("Frame Last", 800, 600);

		//Init Game
	unique_ptr<FrameLastGame> game = make_unique<FrameLastGame>();
	game->Init();

		//Star Field Creation
	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		vec2 pos(random((float)bls::g_renderer.GetWidth()), random((float)bls::g_renderer.GetHeight()));
		vec2 vel(randomf(0.05f*2, 0.5f*2), 0.0f);


		stars.push_back(Star(pos, vel));
	}

	

		//Game Loop
	bool quit = false;
	while (!quit)
	{
			//Update Audio System
		g_audioSystem.Update();

			//Update Engine
		g_time.Tick();

			//Update Input
		g_inputSystem.Update();

			//Update Emitter
		g_particleSystem.Update(g_time.GetDeltaTime());

		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

			//Update Game
		game->Update(g_time.GetDeltaTime());
		
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

			//Game Drawer
		g_renderer.SetColor(255, 255, 255, 255);
		g_particleSystem.Draw(g_renderer);
		game->Draw(g_renderer);

			//End of Frame
		g_renderer.EndFrame();
	}

		//End of File
	return 0;
}