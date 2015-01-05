#pragma once
#include "uutVertexDeclare.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"

namespace uut
{
	struct Vertex3
	{
		DECLARE_VERTEX;

		Vector3f pos;
		Vector2f tex;
		uint32_t color;

		Vertex3() {}
		Vertex3(const Vector3f& pos, const uint32_t color);
		Vertex3(const Vector3f& pos, const Vector2f& tex, const uint32_t color);
	};
}