#pragma once
#include "uutVideoDefs.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"
#include "uutColor.h"

namespace uut
{
	struct Vertex2
	{
		float x, y;
		float u, v;
		uint32_t color;

		static const unsigned SIZE;
		static const unsigned DECLARE_COUNT = 3;
		static const SDeclareType DECLARE[DECLARE_COUNT];

		Vertex2() {}
		Vertex2(const Vector2& pos, const uint32_t color);
	};
}