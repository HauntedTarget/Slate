#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include <iostream>

using namespace bls;
using namespace std;

int main()
{
	int* p = new int;

	delete p;

	cout << "Hello World\n";

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
	}
}