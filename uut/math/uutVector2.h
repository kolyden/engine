#pragma once
#include "math/uutMath.h"

namespace uut
{
	class Vector2f
	{
	public:
		float x, y;

		Vector2f() {}
		Vector2f(float x_, float y_);
		~Vector2f() {}

		bool operator==(const Vector2f &rhs) const;
		bool operator!=(const Vector2f &rhs) const;

		Vector2f &operator+=(const Vector2f &rhs);
		Vector2f &operator-=(const Vector2f &rhs);
		Vector2f &operator*=(float scalar);
		Vector2f &operator/=(float scalar);

		Vector2f operator+(const Vector2f &rhs) const;
		Vector2f operator-(const Vector2f &rhs) const;
		Vector2f operator*(float scalar) const;
		Vector2f operator/(float scalar) const;

		float magnitude() const;
		float magnitudeSq() const;
		Vector2f inverse() const;
		void normalize();
		void set(float x_, float y_);

		static float distance(const Vector2f &pt1, const Vector2f &pt2);
		static float distanceSq(const Vector2f &pt1, const Vector2f &pt2);
		static float dot(const Vector2f &p, const Vector2f &q);
		static Vector2f lerp(const Vector2f &p, const Vector2f &q, float t);
		static void orthogonalize(Vector2f &v1, Vector2f &v2);
		static Vector2f proj(const Vector2f &p, const Vector2f &q);
		static Vector2f perp(const Vector2f &p, const Vector2f &q);
		static Vector2f reflect(const Vector2f &i, const Vector2f &n);

		static const Vector2f ZERO;
		static const Vector2f ONE;

		friend Vector2f operator*(float lhs, const Vector2f &rhs);
		friend Vector2f operator-(const Vector2f &v);
	};

	inline Vector2f operator*(float lhs, const Vector2f &rhs)
	{
		return Vector2f(lhs * rhs.x, lhs * rhs.y);
	}

	inline Vector2f operator-(const Vector2f &v)
	{
		return Vector2f(-v.x, -v.y);
	}

	//////////////////////////////////////////////////////////////////////////
	class Vector2i
	{
	public:
		int x, y;

		Vector2i() {}
		Vector2i(int x_, int y_) : x(x_), y(y_) {}

		static const Vector2i ZERO;
		static const Vector2i ONE;
	};
}