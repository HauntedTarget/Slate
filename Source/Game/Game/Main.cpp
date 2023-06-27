#include "Core/Random.h"
#include "Core/FileIO.h"
#include <iostream>

using namespace bls;
using namespace std;

int main()
{
	cout << "Hello World\n";

	cout << getFilePath() << endl;

	seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 3; i++) {
		cout << random(10, 20) << endl;
	}
}