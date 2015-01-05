#pragma once
#include "uutVertexDeclare.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"

namespace uut
{
	struct Vertex2
	{
		DECLARE_VERTEX;

		Vector2f pos;
		Vector2f tex;
		uint32_t color;

		Vertex2() {}
		Vertex2(const Vector2f& pos, const uint32_t color);
		Vertex2(const Vector2f& pos, const Vector2f& tex, const uint32_t color);
	};
}