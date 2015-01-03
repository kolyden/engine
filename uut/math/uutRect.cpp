#include "math/uutRect.h"

namespace uut
{
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