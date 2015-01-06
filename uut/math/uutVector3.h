#pragma once
#include "math/uutMath.h"

namespace uut
{
	class Vector3f
	{
	public:
		float x, y, z;

		Vector3f() {}
		Vector3f(float x_, float y_, float z_);
		~Vector3f() {}

		bool operator==(const Vector3f &rhs) const;
		bool operator!=(const Vector3f &rhs) const;

		Vector3f &operator+=(const Vector3f &rhs);
		Vector3f &operator-=(const Vector3f &rhs);
		Vector3f &operator*=(float scalar);
		Vector3f &operator/=(float scalar);

		Vector3f operator+(const Vector3f &rhs) const;
		Vector3f operator-(const Vector3f &rhs) const;
		Vector3f operator*(float scalar) const;
		Vector3f operator/(float scalar) const;

		float magnitude() const;
		float magnitudeSq() const;
		Vector3f inverse() const;
		void normalize();
		void set(float x_, float y_, float z_);

		static Vector3f cross(const Vector3f &p, const Vector3f &q);
		static float distance(const Vector3f &pt1, const Vector3f &pt2);
		static float distanceSq(const Vector3f &pt1, const Vector3f &pt2);
		static float dot(const Vector3f &p, const Vector3f &q);
		static Vector3f lerp(const Vector3f &p, const Vector3f &q, float t);
		static void orthogonalize(Vector3f &v1, Vector3f &v2);
		static void orthogonalize(Vector3f &v1, Vector3f &v2, Vector3f &v3);
		static Vector3f proj(const Vector3f &p, const Vector3f &q);
		static Vector3f perp(const Vector3f &p, const Vector3f &q);
		static Vector3f reflect(const Vector3f &i, const Vector3f &n);

		friend Vector3f operator*(float lhs, const Vector3f &rhs);
		friend Vector3f operator-(const Vector3f &v);
	};

	inline Vector3f operator*(float lhs, const Vector3f &rhs)
	{
		return Vector3f(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
	}

	inline Vector3f operator-(const Vector3f &v)
	{
		return Vector3f(-v.x, -v.y, -v.z);
	}
}