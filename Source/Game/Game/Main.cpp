#include <iostream>
#include "../../Engine/Core/Random.h"

using namespace std;
using namespace rando;

int main()
{
	cout << "Hello World\n";

	seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {
		cout << random(10, 20) << endl;
	}
}