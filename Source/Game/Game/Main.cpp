#include "Core/Memory.h"
#include "Core/FileIO.h"
#include "Core/Time.h"
#include "Core/Random.h"
#include "Renderer/Renderer.h"
#include <iostream>

using namespace bls;
using namespace std;

int main()
{
	g_memoryTracker.DisplayInfo();

	int* p = new int;
	g_memoryTracker.DisplayInfo();

	delete p;
	g_memoryTracker.DisplayInfo();

	Time timer;
	for (int i = 0; i < 1000000; i++) {}
	cout << timer.GetElapsedNanoseconds() << endl;

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
}