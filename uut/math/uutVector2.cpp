#include "uutVector2.h"

namespace uut
{
	const Vector2f Vector2f::ZERO(0, 0);
	const Vector2f Vector2f::ONE(1, 1);

	float Vector2f::distance(const Vector2f &pt1, const Vector2f &pt2)
	{
		// Calculates the distance between 2 points.
		return sqrtf(distanceSq(pt1, pt2));
	}

	float Vector2f::distanceSq(const Vector2f &pt1, const Vector2f &pt2)
	{
		// Calculates the squared distance between 2 points.
		return ((pt1.x - pt2.x) * (pt1.x - pt2.x))
			+ ((pt1.y - pt2.y) * (pt1.y - pt2.y));
	}

	float Vector2f::dot(const Vector2f &p, const Vector2f &q)
	{
		return (p.x * q.x) + (p.y * q.y);
	}

	Vector2f Vector2f::lerp(const Vector2f &p, const Vector2f &q, float t)
	{
		// Linearly interpolates from 'p' to 'q' as t varies from 0 to 1.
		return p + t * (q - p);
	}

	void Vector2f::orthogonalize(Vector2f &v1, Vector2f &v2)
	{
		// Performs Gram-Schmidt Orthogonalization on the 2 basis vectors to
		// turn them into orthonormal basis vectors.
		v2 = v2 - proj(v2, v1);
		v2.normalize();
	}

	Vector2f Vector2f::proj(const Vector2f &p, const Vector2f &q)
	{
		// Calculates the projection of 'p' onto 'q'.
		float length = q.magnitude();
		return (Vector2f::dot(p, q) / (length * length)) * q;
	}

	Vector2f Vector2f::perp(const Vector2f &p, const Vector2f &q)
	{
		// Calculates the component of 'p' perpendicular to 'q'.
		float length = q.magnitude();
		return p - ((Vector2f::dot(p, q) / (length * length)) * q);
	}

	Vector2f Vector2f::reflect(const Vector2f &i, const Vector2f &n)
	{
		// Calculates reflection vector from entering ray direction 'i'
		// and surface normal 'n'.
		return i - 2.0f * Vector2f::proj(i, n);
	}

	Vector2f::Vector2f(float x_, float y_) : x(x_), y(y_) {}

	bool Vector2f::operator==(const Vector2f &rhs) const
	{
		return Math::closeEnough(x, rhs.x) && Math::closeEnough(y, rhs.y);
	}

	bool Vector2f::operator!=(const Vector2f &rhs) const
	{
		return !(*this == rhs);
	}

	Vector2f &Vector2f::operator+=(const Vector2f &rhs)
	{
		x += rhs.x, y += rhs.y;
		return *this;
	}

	Vector2f &Vector2f::operator-=(const Vector2f &rhs)
	{
		x -= rhs.x, y -= rhs.y;
		return *this;
	}

	Vector2f &Vector2f::operator*=(float scalar)
	{
		x *= scalar, y *= scalar;
		return *this;
	}

	Vector2f &Vector2f::operator/=(float scalar)
	{
		x /= scalar, y /= scalar;
		return *this;
	}

	Vector2f Vector2f::operator+(const Vector2f &rhs) const
	{
		Vector2f tmp(*this);
		tmp += rhs;
		return tmp;
	}

	Vector2f Vector2f::operator-(const Vector2f &rhs) const
	{
		Vector2f tmp(*this);
		tmp -= rhs;
		return tmp;
	}

	Vector2f Vector2f::operator*(float scalar) const
	{
		return Vector2f(x * scalar, y * scalar);
	}

	Vector2f Vector2f::operator/(float scalar) const
	{
		return Vector2f(x / scalar, y / scalar);
	}

	float Vector2f::magnitude() const
	{
		return sqrtf((x * x) + (y * y));
	}

	float Vector2f::magnitudeSq() const
	{
		return (x * x) + (y * y);
	}

	Vector2f Vector2f::inverse() const
	{
		return Vector2f(-x, -y);
	}

	void Vector2f::normalize()
	{
		float invMag = 1.0f / magnitude();
		x *= invMag, y *= invMag;
	}

	void Vector2f::set(float x_, float y_)
	{
		x = x_, y = y_;
	}

	//////////////////////////////////////////////////////////////////////////
	const Vector2i Vector2i::ZERO(0, 0);
	const Vector2i Vector2i::ONE(1, 1);

}