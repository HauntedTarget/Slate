#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include <iostream>
#include <chrono>

using namespace bls;
using namespace std;
using namespace chrono;

int main()
{
	g_memoryTracker.DisplayInfo();

	int* p = new int;
	g_memoryTracker.DisplayInfo();

	delete p;
	g_memoryTracker.DisplayInfo();

	auto i = true;

	auto start = high_resolution_clock::now();

	for (int i = 0; i < 100000; i++) {}

	auto end = high_resolution_clock::now();

	cout << (end - start).count();

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