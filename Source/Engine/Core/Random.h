#pragma once
#include <random>

namespace rando
{
	void seedRandom(int seed) { srand(seed); }
	int random() { return rand(); }
}