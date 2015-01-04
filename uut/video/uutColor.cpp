#include "uutColor.h"

namespace uut
{
    const Color Color::WHITE(1, 1, 1);
    const Color Color::BLACK(0, 0, 0);
    const Color Color::RED(1, 0, 0);
    const Color Color::GREEN(0, 1, 0);
    const Color Color::BLUE(0, 0, 1);

    Color::Color() {}

    Color::Color(float r, float g, float b, float a /* = 1.0f */)
        : _r(r), _g(g), _b(b), _a(a)
    {
    }

	Color::Color(uint32_t color)
	{
		const float inv = 1.0f / 255.0f;
		_r = inv * ((color >> 24) & 0xFF);
		_g = inv * ((color >> 16) & 0xFF);
		_b = inv * ((color >>  8) & 0xFF);
		_a = inv * ((color      ) & 0xFF);
	}

    void Color::Convert(uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const
    {
        if (r) *r = static_cast<uint8_t>(_r * 255.0f);
        if (g) *g = static_cast<uint8_t>(_g * 255.0f);
        if (b) *b = static_cast<uint8_t>(_b * 255.0f);
        if (a) *a = static_cast<uint8_t>(_a * 255.0f);
    }

	uint32_t Color::ToUint() const
	{
		uint8_t r, g, b, a;
		Convert(&r, &g, &b, &a);

		return (uint32_t)((r << 24) + (g << 16) + (b << 8) + a);
	}
}