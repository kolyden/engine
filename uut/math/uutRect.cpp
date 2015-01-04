#include "math/uutRect.h"

namespace uut
{
	Rect::Rect() {}
	Rect::Rect(float x, float y, float w, float h)
		: _pos(x, y), _size(w, h)
	{
	}

	Rect::Rect(const Vector2& pos, const Vector2& size)
		: _pos(pos), _size(size)
	{
	}

	//////////////////////////////////////////////////////////////////////////
    Recti::Recti() {}
    Recti::Recti(int x, int y, int w, int h)
        : _pos(x, y), _size(w, h)
    {
    }

    Recti::Recti(const Vector2i& pos, const Vector2i& size)
        : _pos(pos), _size(size)
    {
    }
}