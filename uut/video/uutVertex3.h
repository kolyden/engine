#pragma once
#include "uutVideoDefs.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"

namespace uut
{
	struct Vertex3
	{
		Vector3f pos;
		Vector2f tex;
		uint32_t color;

		static const unsigned SIZE;
		static const unsigned DECLARE_COUNT = 3;
		static const SDeclareType DECLARE[DECLARE_COUNT];

		Vertex3() {}
		Vertex3(const Vector3f& pos, const uint32_t color);
		Vertex3(const Vector3f& pos, const Vector2f& tex, const uint32_t color);
	};
}