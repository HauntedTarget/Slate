#include "Core/Memory.h"
#include "Core/FileIO.h"
#include "Core/Time.h"
#include "Core/Random.h"
#include "Renderer/Renderer.h"
#include <iostream>

using namespace bls;
using namespace std;

int main(int argc, char* argv[])
{

	Renderer renderer;

	renderer.Initialize();

	renderer.CreateWindow("SlateEngine", 800, 600);

	while (true) {
		renderer.SetColor(0, 0, 0, 255);

		//renderer.BeginFrame();
		for (int i = 0; i < 1000; i++) {
			renderer.SetColor(random(156), random(156), random(156), 255);
			renderer.DrawLine(random(renderer.GetWidth()), random(renderer.GetHeight()), random(renderer.GetWidth()), random(renderer.GetHeight()));
			renderer.SetColor(random(256), random(256), random(256), 255);
			renderer.DrawPoint(random(renderer.GetWidth()), random(renderer.GetHeight()));

		}
		//draw
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