#pragma once
#include "math/uutVector2.h"

namespace uut
{
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