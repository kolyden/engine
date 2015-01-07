#include "uutVertex3.h"

namespace uut
{
	IMPLEMENT_VERTEX(Vertex3, (
	{ 0, USAGE_POSITION, 3, VALUE_FLOAT, 0 },
	{ 0, USAGE_TEXCOORDS, 2, VALUE_FLOAT, offsetof(Vertex3, tex.x) },
	{ 0, USAGE_COLOR, 4, VALUE_UBYTE, offsetof(Vertex3, color) }));


	Vertex3::Vertex3(const Vector3f& _pos, const uint32_t _color)
		: pos(_pos), tex(Vector2f::ZERO), color(_color)
	{
	}

	Vertex3::Vertex3(const Vector3f& _pos, const Vector2f& _tex, const uint32_t _color)
		: pos(_pos), tex(_tex), color(_color)
	{
	}
}