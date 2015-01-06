#include "uutRandom.h"
#include <cstdlib>

namespace uut
{
	float Random::random(float min, float max)
	{
		// Returns a random number in range [min,max].

		return min + (max - min)
			* (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
	}

}