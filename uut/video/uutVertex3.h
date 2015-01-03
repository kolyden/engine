#pragma once
#include "uutVideoDefs.h"
#include "math/uutVector3.h"

namespace uut
{
	struct Vertex3
	{
		Vector3 pos;
		Vector3 tex;
		uint32_t color;

		static const unsigned SIZE;
		static const unsigned DECLARE_COUNT = 3;
		static const SDeclareType DECLARE[DECLARE_COUNT];

		Vertex3() {}
		Vertex3(const Vector3& pos, const uint32_t color);
		Vertex3(const Vector3& pos, const Vector3& tex, const uint32_t color);
	};
}