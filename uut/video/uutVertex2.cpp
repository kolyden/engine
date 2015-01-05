#include "uutVertex2.h"

namespace uut
{
	IMPLEMENT_VERTEX(Vertex2,(
	{ 0, USAGE_POSITION, 2, VALUE_FLOAT, 0 },
	{ 0, USAGE_TEXCOORDS, 2, VALUE_FLOAT, offsetof(Vertex2, tex.x) },
	{ 0, USAGE_COLOR, 4, VALUE_UBYTE, offsetof(Vertex2, color) }));

	Vertex2::Vertex2(const Vector2f& _pos, const uint32_t _color)
		: pos(_pos), tex(Vector2f::ZERO), color(_color)
	{
	}

	Vertex2::Vertex2(const Vector2f& _pos, const Vector2f& _tex, const uint32_t _color)
		: pos(_pos), tex(_tex), color(_color)
	{
	}
}