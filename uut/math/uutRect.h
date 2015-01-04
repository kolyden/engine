#pragma once
#include "math/uutVector2.h"

namespace uut
{
	template<class T>
	class Rect
	{
	public:
		Rect() {}
		Rect(T x, T y, T w, T h) : pos(x, y), size(w, h) {}
		Rect(const Vector2<T>& _pos, const Vector2<T>& _size)
			: pos(_pos), size(_size) {}

		Vector2<T> pos;
		Vector2<T> size;
	};

	typedef Rect<float> Rectf;
	typedef Rect<int> Recti;
}