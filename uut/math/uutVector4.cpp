#include "uutVector4.h"
#include "uutVector3.h"

namespace uut
{
	float Vector4f::distance(const Vector4f &pt1, const Vector4f &pt2)
	{
		// Calculates the distance between 2 points.
		return sqrtf(distanceSq(pt1, pt2));
	}

	float Vector4f::distanceSq(const Vector4f &pt1, const Vector4f &pt2)
	{
		// Calculates the squared distance between 2 points.
		return ((pt1.x - pt2.x) * (pt1.x - pt2.x))
			+ ((pt1.y - pt2.y) * (pt1.y - pt2.y))
			+ ((pt1.z - pt2.z) * (pt1.z - pt2.z))
			+ ((pt1.w - pt2.w) * (pt1.w - pt2.w));
	}

	float Vector4f::dot(const Vector4f &p, const Vector4f &q)
	{
		return (p.x * q.x) + (p.y * q.y) + (p.z * q.z) + (p.w * q.w);
	}

	Vector4f Vector4f::lerp(const Vector4f &p, const Vector4f &q, float t)
	{
		// Linearly interpolates from 'p' to 'q' as t varies from 0 to 1.
		return p + t * (q - p);
	}

	Vector4f::Vector4f(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}

	Vector4f::Vector4f(const Vector3f &v, float w_) : x(v.x), y(v.y), z(v.z), w(w_) {}

	Vector4f &Vector4f::operator+=(const Vector4f &rhs)
	{
		x += rhs.x, y += rhs.y, z += rhs.z, w += rhs.w;
		return *this;
	}

	bool Vector4f::operator==(const Vector4f &rhs) const
	{
		return Math::closeEnough(x, rhs.x) && Math::closeEnough(y, rhs.y)
			&& Math::closeEnough(z, rhs.z) && Math::closeEnough(w, rhs.w);
	}

	bool Vector4f::operator!=(const Vector4f &rhs) const
	{
		return !(*this == rhs);
	}

	Vector4f &Vector4f::operator-=(const Vector4f &rhs)
	{
		x -= rhs.x, y -= rhs.y, z -= rhs.z, w -= rhs.w;
		return *this;
	}

	Vector4f &Vector4f::operator*=(float scalar)
	{
		x *= scalar, y *= scalar, z *= scalar, w *= scalar;
		return *this;
	}

	Vector4f &Vector4f::operator/=(float scalar)
	{
		x /= scalar, y /= scalar, z /= scalar, w /= scalar;
		return *this;
	}

	Vector4f Vector4f::operator+(const Vector4f &rhs) const
	{
		Vector4f tmp(*this);
		tmp += rhs;
		return tmp;
	}

	Vector4f Vector4f::operator-(const Vector4f &rhs) const
	{
		Vector4f tmp(*this);
		tmp -= rhs;
		return tmp;
	}

	Vector4f Vector4f::operator*(float scalar) const
	{
		return Vector4f(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	Vector4f Vector4f::operator/(float scalar) const
	{
		return Vector4f(x / scalar, y / scalar, z / scalar, w / scalar);
	}

	float Vector4f::magnitude() const
	{
		return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
	}

	float Vector4f::magnitudeSq() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	Vector4f Vector4f::inverse() const
	{
		return Vector4f(-x, -y, -z, -w);
	}

	void Vector4f::normalize()
	{
		float invMag = 1.0f / magnitude();
		x *= invMag, y *= invMag, z *= invMag, w *= invMag;
	}

	void Vector4f::set(float x_, float y_, float z_, float w_)
	{
		x = x_, y = y_, z = z_, w = w_;
	}

	Vector3f Vector4f::toVector3() const
	{
		return (w != 0.0f) ? Vector3f(x / w, y / w, z / w) : Vector3f(x, y, z);
	}
}