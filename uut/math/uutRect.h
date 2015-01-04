#pragma once
#include "math/uutVector2.h"

namespace uut
{
	class Rect
	{
	public:
		Rect();
		Rect(float x, float y, float w, float h);
		Rect(const Vector2& pos, const Vector2& size);

		Vector2 _pos;
		Vector2 _size;
	};

    class Recti
    {
    public:
        Recti();
        Recti(int x, int y, int w, int h);
        Recti(const Vector2i& pos, const Vector2i& size);

        Vector2i _pos;
        Vector2i _size;
    };
}