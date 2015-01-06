#include "uutMath.h"

namespace uut
{
	const float Math::PI = 3.1415926f;
	const float Math::HALF_PI = Math::PI / 2.0f;
	const float Math::QUARTER_PI = Math::PI / 4.0f;
	const float Math::TWO_PI = Math::PI * 2.0f;
	const float Math::EPSILON = 1e-6f;

	const float Math::DEGTORAD = PI / 180.0f;
	const float Math::DEGTORAD_2 = PI / 360.0f;
	const float Math::RADTODEG = 1.0f / DEGTORAD;

	int Math::nextPower2(int x)
	{
		int i = x & (~x + 1);

		while (i < x)
			i <<= 1;

		return i;
	}
}