#pragma once
#include "core/uutDefine.h"

namespace uut
{
    class UUT_API Color
    {
    public:
        Color();
        Color(float r, float g, float b, float a = 1.0f);

        void Convert(uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const;
		uint32_t ToUint() const;

        float _r;
        float _g;
        float _b;
        float _a;

        static const Color WHITE;
        static const Color BLACK;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
   };
}