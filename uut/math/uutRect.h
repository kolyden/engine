#pragma once
#include "math/uutVector2.h"

namespace uut
{
	class Rectf
	{
	public:
		Rectf() {}
		Rectf(float x, float y, float w, float h) : pos(x, y), size(w, h) {}
		Rectf(const Vector2f& _pos, const Vector2f& _size)
			: pos(_pos), size(_size) {}

		Vector2f pos;
		Vector2f size;
	};

	class Recti
	{
	public:
		Recti() {}
		Recti(int x, int y, int w, int h) : pos(x, y), size(w, h) {}
		Recti(const Vector2i& _pos, const Vector2i& _size)
			: pos(_pos), size(_size) {}

		Vector2i pos;
		Vector2i size;
	};
}