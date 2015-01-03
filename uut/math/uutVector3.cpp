#include "math/uutVector3.h"

namespace uut
{
	const Vector3 Vector3::ZERO(0, 0, 0);
	const Vector3 Vector3::LEFT(-1, 0, 0);
	const Vector3 Vector3::RIGHT(+1, 0, 0);
	const Vector3 Vector3::UP(0, +1, 0);
	const Vector3 Vector3::DOWN(0, -1, 0);
	const Vector3 Vector3::ONE(1, 1, 1);

	Vector3::Vector3(const Vector3i& vector)
		: _x((float)vector._x)
		, _y((float)vector._y)
	{}

	//////////////////////////////////////////////////////////////////////////
	const Vector3i Vector3i::ZERO(0, 0, 0);
	const Vector3i Vector3i::LEFT(-1, 0, 0);
	const Vector3i Vector3i::RIGHT(+1, 0, 0);
	const Vector3i Vector3i::UP(0, +1, 0);
	const Vector3i Vector3i::DOWN(0, -1, 0);
	const Vector3i Vector3i::ONE(1, 1, 1);

	Vector3i::Vector3i(const Vector3& rhs)
		: _x(Math::RoundToInt(rhs._x))
		, _y(Math::RoundToInt(rhs._y))
	{
	}
}