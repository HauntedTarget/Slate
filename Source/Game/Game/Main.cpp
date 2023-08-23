	//Included Files (Always needed)
#include "Core/Core.h"
#include "Framework/Framework.h"
	//Included Files (Always needed)
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "FrameLastGame.h"
#include "Physics/PhysicsSystem.h"
	//Included Libs (Always needed)
#include <functional>
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <array>
#include <map>

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

void print(int i)
{
	cout << i << endl;
}

int add(int i1, int i2)
{
	return i1 + i2;
}

int sub(int i1, int i2)
{
	return i1 - i2;
}

class A
{
public:
	int add(int i1, int i2)
	{
		return i1 + i2;
	}
};

//Main Function
int main(int argc, char* argv[])
{
	void (*func_ptr)(int) = &print;
	func_ptr(5);

	int (*op_ptr)(int, int);

	op_ptr = sub;

	cout << op_ptr(4, 4) << endl;

	function<int(int, int)> op;
	op = add;

	cout << op(4, 4) << endl;

	A a;
	op = bind(&A::add, &a, placeholders::_1, placeholders::_2);
	cout << op(5, 5) << endl;

	/*Testing Json.h*/
	/*MemoryTracker::Initialize();
	seedRandom((unsigned int)time(nullptr));
	setFilePath("assets");
	rapidjson::Document document;
	Json::Load("json.txt", document);
	int i1;
	Json::Read(document, "integer1", i1);
	cout << i1 << endl;
	int i2;
	Json::Read(document, "integer2", i2);
	cout << i2 << endl;
	int i3;
	Json::Read(document, "AHHHHHHH", i3);
	cout << i3 << endl;
	int i4;
	Json::Read(document, "Whyyyyyy", i4);
	cout << i4 << endl;*/

		//Start of Game Info Log
	INFO_LOG("Game Started");

		//MemTracker Init
	MemoryTracker::Initialize();

		//Sets "Random" Seed
	seedRandom((unsigned int)time(nullptr));

		//Init Systems
	g_audioSystem.Initialize();
	g_renderer.Initialize();
	g_inputSystem.Initialize();
	PhysicsSystem::Instance().Initialize();

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
		vec2 pos((float)random((int)bls::g_renderer.GetWidth()), (float)random((int)bls::g_renderer.GetHeight()));
		vec2 vel(randomf(0.05f*2, 0.5f*2), 0.0f);


		stars.push_back(Star(pos, vel));
	}

		// create texture
	//shatr<bls::Texture> texture = bls::g_resources.Get<bls::Texture>("Ship.png", bls::g_renderer);

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

			//Draw Texture
		//g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

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