#include "uutVertex2.h"

namespace uut
{
	const unsigned Vertex2::SIZE = sizeof(Vertex2);
	const SDeclareType Vertex2::DECLARE[Vertex2::DECLARE_COUNT] =
	{
		{ 0, USAGE_POSITION, 2, VALUE_FLOAT, 0 },
		{ 0, USAGE_TEXCOORDS, 2, VALUE_FLOAT, offsetof(Vertex2, u) },
		{ 0, USAGE_COLOR, 4, VALUE_UBYTE, offsetof(Vertex2, color) }
	};

	Vertex2::Vertex2(const Vector2& _pos, const uint32_t _color)
		: x(_pos._x), y(_pos._y), u(0), v(0), color(_color)
	{
	}

	Vertex2::Vertex2(const Vector2& _pos, const Vector2& _tex, const uint32_t _color)
		: x(_pos._x), y(_pos._y), u(_tex._x), v(_tex._y), color(_color)
	{
	}
}