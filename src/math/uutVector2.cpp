#include "math/uutVector2.h"

namespace uut
{
    const Vector2 Vector2::ZERO(0, 0);
    const Vector2 Vector2::LEFT(-1, 0);
    const Vector2 Vector2::RIGHT(+1, 0);
    const Vector2 Vector2::UP(0, +1);
    const Vector2 Vector2::DOWN(0, -1);
    const Vector2 Vector2::ONE(1, 1);

	Vector2::Vector2(const Vector2i& vector)
		: _x((float)vector._x)
		, _y((float)vector._y)
	{}

	//////////////////////////////////////////////////////////////////////////
	const Vector2i Vector2i::ZERO(0, 0);
	const Vector2i Vector2i::LEFT(-1, 0);
	const Vector2i Vector2i::RIGHT(+1, 0);
	const Vector2i Vector2i::UP(0, +1);
	const Vector2i Vector2i::DOWN(0, -1);
	const Vector2i Vector2i::ONE(1, 1);

	Vector2i::Vector2i(const Vector2& rhs)
		: _x(Math::RoundToInt(rhs._x))
		, _y(Math::RoundToInt(rhs._y))
	{
	}
}