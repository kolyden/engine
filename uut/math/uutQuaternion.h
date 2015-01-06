#pragma once
#include "uutVector3.h"
#include "uutMatrix3.h"
#include "uutMatrix4.h"

namespace uut
{
	class Quaternionf
	{
	public:
		static const Quaternionf IDENTITY;

		float w, x, y, z;

		static Quaternionf slerp(const Quaternionf &a, const Quaternionf &b, float t);

		Quaternionf() {}
		Quaternionf(float w_, float x_, float y_, float z_);
		Quaternionf(float headDegrees, float pitchDegrees, float rollDegrees);
		Quaternionf(const Vector3f &axis, float degrees);
		explicit Quaternionf(const Matrix3f &m);
		explicit Quaternionf(const Matrix4f &m);
		~Quaternionf() {}

		bool operator==(const Quaternionf &rhs) const;
		bool operator!=(const Quaternionf &rhs) const;

		Quaternionf &operator+=(const Quaternionf &rhs);
		Quaternionf &operator-=(const Quaternionf &rhs);
		Quaternionf &operator*=(const Quaternionf &rhs);
		Quaternionf &operator*=(float scalar);
		Quaternionf &operator/=(float scalar);

		Quaternionf operator+(const Quaternionf &rhs) const;
		Quaternionf operator-(const Quaternionf &rhs) const;
		Quaternionf operator*(const Quaternionf &rhs) const;
		Quaternionf operator*(float scalar) const;
		Quaternionf operator/(float scalar) const;

		Quaternionf conjugate() const;
		void fromAxisAngle(const Vector3f &axis, float degrees);
		void fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
		void fromMatrix(const Matrix3f &m);
		void fromMatrix(const Matrix4f &m);
		void identity();
		Quaternionf inverse() const;
		float magnitude() const;
		void normalize();
		void set(float w_, float x_, float y_, float z_);
		void toAxisAngle(Vector3f &axis, float &degrees) const;
		void toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const;
		Matrix3f toMatrix3() const;
		Matrix4f toMatrix4() const;

		friend Quaternionf operator*(float lhs, const Quaternionf &rhs);
	};

	inline Quaternionf operator*(float lhs, const Quaternionf &rhs)
	{
		return rhs * lhs;
	}

	inline Quaternionf::Quaternionf(float w_, float x_, float y_, float z_)
		: w(w_), x(x_), y(y_), z(z_) {}

	inline Quaternionf::Quaternionf(float headDegrees, float pitchDegrees, float rollDegrees)
	{
		fromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
	}

	inline Quaternionf::Quaternionf(const Vector3f &axis, float degrees)
	{
		fromAxisAngle(axis, degrees);
	}

	inline Quaternionf::Quaternionf(const Matrix3f &m)
	{
		fromMatrix(m);
	}

	inline Quaternionf::Quaternionf(const Matrix4f &m)
	{
		fromMatrix(m);
	}

	inline bool Quaternionf::operator==(const Quaternionf &rhs) const
	{
		return Math::closeEnough(w, rhs.w) && Math::closeEnough(x, rhs.x)
			&& Math::closeEnough(y, rhs.y) && Math::closeEnough(z, rhs.z);
	}

	inline bool Quaternionf::operator!=(const Quaternionf &rhs) const
	{
		return !(*this == rhs);
	}

	inline Quaternionf &Quaternionf::operator+=(const Quaternionf &rhs)
	{
		w += rhs.w, x += rhs.x, y += rhs.y, z += rhs.z;
		return *this;
	}

	inline Quaternionf &Quaternionf::operator-=(const Quaternionf &rhs)
	{
		w -= rhs.w, x -= rhs.x, y -= rhs.y, z -= rhs.z;
		return *this;
	}

	inline Quaternionf &Quaternionf::operator*=(const Quaternionf &rhs)
	{
		// Multiply so that rotations are applied in a left to right order.
		Quaternionf tmp(
			(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
			(w * rhs.x) + (x * rhs.w) - (y * rhs.z) + (z * rhs.y),
			(w * rhs.y) + (x * rhs.z) + (y * rhs.w) - (z * rhs.x),
			(w * rhs.z) - (x * rhs.y) + (y * rhs.x) + (z * rhs.w));

		/*
		// Multiply so that rotations are applied in a right to left order.
		Quaternion tmp(
		(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
		(w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y),
		(w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x),
		(w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w));
		*/

		*this = tmp;
		return *this;
	}

	inline Quaternionf &Quaternionf::operator*=(float scalar)
	{
		w *= scalar, x *= scalar, y *= scalar, z *= scalar;
		return *this;
	}

	inline Quaternionf &Quaternionf::operator/=(float scalar)
	{
		w /= scalar, x /= scalar, y /= scalar, z /= scalar;
		return *this;
	}

	inline Quaternionf Quaternionf::operator+(const Quaternionf &rhs) const
	{
		Quaternionf tmp(*this);
		tmp += rhs;
		return tmp;
	}

	inline Quaternionf Quaternionf::operator-(const Quaternionf &rhs) const
	{
		Quaternionf tmp(*this);
		tmp -= rhs;
		return tmp;
	}

	inline Quaternionf Quaternionf::operator*(const Quaternionf &rhs) const
	{
		Quaternionf tmp(*this);
		tmp *= rhs;
		return tmp;
	}

	inline Quaternionf Quaternionf::operator*(float scalar) const
	{
		Quaternionf tmp(*this);
		tmp *= scalar;
		return tmp;
	}

	inline Quaternionf Quaternionf::operator/(float scalar) const
	{
		Quaternionf tmp(*this);
		tmp /= scalar;
		return tmp;
	}

	inline Quaternionf Quaternionf::conjugate() const
	{
		Quaternionf tmp(w, -x, -y, -z);
		return tmp;
	}

	inline void Quaternionf::fromAxisAngle(const Vector3f &axis, float degrees)
	{
		float halfTheta = Math::degreesToRadians(degrees) * 0.5f;
		float s = sinf(halfTheta);
		w = cosf(halfTheta), x = axis.x * s, y = axis.y * s, z = axis.z * s;
	}

	inline void Quaternionf::fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees)
	{
		Matrix3f m;
		m.fromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
		fromMatrix(m);
	}

	inline void Quaternionf::identity()
	{
		w = 1.0f, x = y = z = 0.0f;
	}

	inline Quaternionf Quaternionf::inverse() const
	{
		float invMag = 1.0f / magnitude();
		return conjugate() * invMag;
	}

	inline float Quaternionf::magnitude() const
	{
		return sqrtf(w * w + x * x + y * y + z * z);
	}

	inline void Quaternionf::normalize()
	{
		float invMag = 1.0f / magnitude();
		w *= invMag, x *= invMag, y *= invMag, z *= invMag;
	}

	inline void Quaternionf::set(float w_, float x_, float y_, float z_)
	{
		w = w_, x = x_, y = y_, z = z_;
	}

	inline void Quaternionf::toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const
	{
		Matrix3f m = toMatrix3();
		m.toHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
	}
}