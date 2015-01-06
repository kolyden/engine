#include "uutVector3.h"

namespace uut
{
	Vector3f Vector3f::cross(const Vector3f &p, const Vector3f &q)
	{
		return Vector3f((p.y * q.z) - (p.z * q.y),
			(p.z * q.x) - (p.x * q.z),
			(p.x * q.y) - (p.y * q.x));
	}

	float Vector3f::distance(const Vector3f &pt1, const Vector3f &pt2)
	{
		// Calculates the distance between 2 points.
		return sqrtf(distanceSq(pt1, pt2));
	}

	float Vector3f::distanceSq(const Vector3f &pt1, const Vector3f &pt2)
	{
		// Calculates the squared distance between 2 points.
		return ((pt1.x - pt2.x) * (pt1.x - pt2.x))
			+ ((pt1.y - pt2.y) * (pt1.y - pt2.y))
			+ ((pt1.z - pt2.z) * (pt1.z - pt2.z));
	}

	float Vector3f::dot(const Vector3f &p, const Vector3f &q)
	{
		return (p.x * q.x) + (p.y * q.y) + (p.z * q.z);
	}

	Vector3f Vector3f::lerp(const Vector3f &p, const Vector3f &q, float t)
	{
		// Linearly interpolates from 'p' to 'q' as t varies from 0 to 1.
		return p + t * (q - p);
	}

	void Vector3f::orthogonalize(Vector3f &v1, Vector3f &v2)
	{
		// Performs Gram-Schmidt Orthogonalization on the 2 basis vectors to
		// turn them into orthonormal basis vectors.
		v2 = v2 - proj(v2, v1);
		v2.normalize();
	}

	void Vector3f::orthogonalize(Vector3f &v1, Vector3f &v2, Vector3f &v3)
	{
		// Performs Gram-Schmidt Orthogonalization on the 3 basis vectors to
		// turn them into orthonormal basis vectors.

		v2 = v2 - proj(v2, v1);
		v2.normalize();

		v3 = v3 - proj(v3, v1) - proj(v3, v2);
		v3.normalize();
	}

	Vector3f Vector3f::proj(const Vector3f &p, const Vector3f &q)
	{
		// Calculates the projection of 'p' onto 'q'.
		float length = q.magnitude();
		return (Vector3f::dot(p, q) / (length * length)) * q;
	}

	Vector3f Vector3f::perp(const Vector3f &p, const Vector3f &q)
	{
		// Calculates the component of 'p' perpendicular to 'q'.
		float length = q.magnitude();
		return p - ((Vector3f::dot(p, q) / (length * length)) * q);
	}

	Vector3f Vector3f::reflect(const Vector3f &i, const Vector3f &n)
	{
		// Calculates reflection vector from entering ray direction 'i'
		// and surface normal 'n'.
		return i - 2.0f * Vector3f::proj(i, n);
	}

	Vector3f::Vector3f(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

	Vector3f &Vector3f::operator+=(const Vector3f &rhs)
	{
		x += rhs.x, y += rhs.y, z += rhs.z;
		return *this;
	}

	bool Vector3f::operator==(const Vector3f &rhs) const
	{
		return Math::closeEnough(x, rhs.x) && Math::closeEnough(y, rhs.y)
			&& Math::closeEnough(z, rhs.z);
	}

	bool Vector3f::operator!=(const Vector3f &rhs) const
	{
		return !(*this == rhs);
	}

	Vector3f &Vector3f::operator-=(const Vector3f &rhs)
	{
		x -= rhs.x, y -= rhs.y, z -= rhs.z;
		return *this;
	}

	Vector3f &Vector3f::operator*=(float scalar)
	{
		x *= scalar, y *= scalar, z *= scalar;
		return *this;
	}

	Vector3f &Vector3f::operator/=(float scalar)
	{
		x /= scalar, y /= scalar, z /= scalar;
		return *this;
	}

	Vector3f Vector3f::operator+(const Vector3f &rhs) const
	{
		Vector3f tmp(*this);
		tmp += rhs;
		return tmp;
	}

	Vector3f Vector3f::operator-(const Vector3f &rhs) const
	{
		Vector3f tmp(*this);
		tmp -= rhs;
		return tmp;
	}

	Vector3f Vector3f::operator*(float scalar) const
	{
		return Vector3f(x * scalar, y * scalar, z * scalar);
	}

	Vector3f Vector3f::operator/(float scalar) const
	{
		return Vector3f(x / scalar, y / scalar, z / scalar);
	}

	float Vector3f::magnitude() const
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	float Vector3f::magnitudeSq() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	Vector3f Vector3f::inverse() const
	{
		return Vector3f(-x, -y, -z);
	}

	void Vector3f::normalize()
	{
		float invMag = 1.0f / magnitude();
		x *= invMag, y *= invMag, z *= invMag;
	}

	void Vector3f::set(float x_, float y_, float z_)
	{
		x = x_, y = y_, z = z_;
	}
}