#pragma once
#include "uutMath.h"

namespace uut
{
	class Vector3f;

	class Vector4f
	{
	public:
		float x, y, z, w;

		static float distance(const Vector4f &pt1, const Vector4f &pt2);
		static float distanceSq(const Vector4f &pt1, const Vector4f &pt2);
		static float dot(const Vector4f &p, const Vector4f &q);
		static Vector4f lerp(const Vector4f &p, const Vector4f &q, float t);

		Vector4f() {}
		Vector4f(float x_, float y_, float z_, float w_);
		Vector4f(const Vector3f &v, float w_);
		~Vector4f() {}

		bool operator==(const Vector4f &rhs) const;
		bool operator!=(const Vector4f &rhs) const;

		Vector4f &operator+=(const Vector4f &rhs);
		Vector4f &operator-=(const Vector4f &rhs);
		Vector4f &operator*=(float scalar);
		Vector4f &operator/=(float scalar);

		Vector4f operator+(const Vector4f &rhs) const;
		Vector4f operator-(const Vector4f &rhs) const;
		Vector4f operator*(float scalar) const;
		Vector4f operator/(float scalar) const;

		float magnitude() const;
		float magnitudeSq() const;
		Vector4f inverse() const;
		void normalize();
		void set(float x_, float y_, float z_, float w_);
		Vector3f toVector3() const;

		friend Vector4f operator*(float lhs, const Vector4f &rhs);
		friend Vector4f operator-(const Vector4f &v);
	};

	inline Vector4f operator*(float lhs, const Vector4f &rhs)
	{
		return Vector4f(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
	}

	inline Vector4f operator-(const Vector4f &v)
	{
		return Vector4f(-v.x, -v.y, -v.z, -v.w);
	}
}