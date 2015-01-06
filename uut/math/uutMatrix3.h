#pragma once
#include "uutVector3.h"

namespace uut
{
	class Matrix3f
	{
	public:
		static const Matrix3f IDENTITY;
		static Matrix3f createFromAxes(const Vector3f &x, const Vector3f &y, const Vector3f &z);
		static Matrix3f createFromAxesTransposed(const Vector3f &x, const Vector3f &y, const Vector3f &z);
		static Matrix3f createFromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
		static Matrix3f createMirror(const Vector3f &planeNormal);
		static Matrix3f createOrient(const Vector3f &from, const Vector3f &to);
		static Matrix3f createRotate(const Vector3f &axis, float degrees);
		static Matrix3f createScale(float sx, float sy, float sz);

		Matrix3f() {}
		Matrix3f(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33);
		~Matrix3f() {}

		float *operator[](int row);
		const float *operator[](int row) const;

		bool operator==(const Matrix3f &rhs) const;
		bool operator!=(const Matrix3f &rhs) const;

		Matrix3f &operator+=(const Matrix3f &rhs);
		Matrix3f &operator-=(const Matrix3f &rhs);
		Matrix3f &operator*=(const Matrix3f &rhs);
		Matrix3f &operator*=(float scalar);
		Matrix3f &operator/=(float scalar);

		Matrix3f operator+(const Matrix3f &rhs) const;
		Matrix3f operator-(const Matrix3f &rhs) const;
		Matrix3f operator*(const Matrix3f &rhs) const;
		Matrix3f operator*(float scalar) const;
		Matrix3f operator/(float scalar) const;

		float determinant() const;
		void fromAxes(const Vector3f &x, const Vector3f &y, const Vector3f &z);
		void fromAxesTransposed(const Vector3f &x, const Vector3f &y, const Vector3f &z);
		void fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
		void identity();
		Matrix3f inverse() const;
		void orient(const Vector3f &from, const Vector3f &to);
		void rotate(const Vector3f &axis, float degrees);
		void scale(float sx, float sy, float sz);
		void toAxes(Vector3f &x, Vector3f &y, Vector3f &z) const;
		void toAxesTransposed(Vector3f &x, Vector3f &y, Vector3f &z) const;
		void toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const;
		Matrix3f transpose() const;

	private:
		float mtx[3][3];

		friend Vector3f operator*(const Vector3f &lhs, const Matrix3f &rhs);
		friend Matrix3f operator*(float scalar, const Matrix3f &rhs);
	};

	inline Vector3f operator*(const Vector3f &lhs, const Matrix3f &rhs)
	{
		return Vector3f(
			(lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[1][0]) + (lhs.z * rhs.mtx[2][0]),
			(lhs.x * rhs.mtx[0][1]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[2][1]),
			(lhs.x * rhs.mtx[0][2]) + (lhs.y * rhs.mtx[1][2]) + (lhs.z * rhs.mtx[2][2]));
	}

	inline Matrix3f operator*(float scalar, const Matrix3f &rhs)
	{
		return rhs * scalar;
	}

	inline Matrix3f Matrix3f::createFromAxes(const Vector3f &x, const Vector3f &y, const Vector3f &z)
	{
		Matrix3f tmp;
		tmp.createFromAxes(x, y, z);
		return tmp;
	}

	inline Matrix3f Matrix3f::createFromAxesTransposed(const Vector3f &x, const Vector3f &y, const Vector3f &z)
	{
		Matrix3f tmp;
		tmp.fromAxesTransposed(x, y, z);
		return tmp;
	}

	inline Matrix3f Matrix3f::createFromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees)
	{
		Matrix3f tmp;
		tmp.fromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
		return tmp;
	}

	inline Matrix3f Matrix3f::createOrient(const Vector3f &from, const Vector3f &to)
	{
		Matrix3f tmp;
		tmp.orient(from, to);
		return tmp;
	}

	inline Matrix3f Matrix3f::createRotate(const Vector3f &axis, float degrees)
	{
		Matrix3f tmp;
		tmp.rotate(axis, degrees);
		return tmp;
	}

	inline Matrix3f Matrix3f::createScale(float sx, float sy, float sz)
	{
		Matrix3f tmp;
		tmp.scale(sx, sy, sz);
		return tmp;
	}

	inline Matrix3f::Matrix3f(float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33)
	{
		mtx[0][0] = m11, mtx[0][1] = m12, mtx[0][2] = m13;
		mtx[1][0] = m21, mtx[1][1] = m22, mtx[1][2] = m23;
		mtx[2][0] = m31, mtx[2][1] = m32, mtx[2][2] = m33;
	}

	inline float *Matrix3f::operator[](int row)
	{
		return mtx[row];
	}

	inline const float *Matrix3f::operator[](int row) const
	{
		return mtx[row];
	}

	inline bool Matrix3f::operator==(const Matrix3f &rhs) const
	{
		return Math::closeEnough(mtx[0][0], rhs.mtx[0][0])
			&& Math::closeEnough(mtx[0][1], rhs.mtx[0][1])
			&& Math::closeEnough(mtx[0][2], rhs.mtx[0][2])
			&& Math::closeEnough(mtx[1][0], rhs.mtx[1][0])
			&& Math::closeEnough(mtx[1][1], rhs.mtx[1][1])
			&& Math::closeEnough(mtx[1][2], rhs.mtx[1][2])
			&& Math::closeEnough(mtx[2][0], rhs.mtx[2][0])
			&& Math::closeEnough(mtx[2][1], rhs.mtx[2][1])
			&& Math::closeEnough(mtx[2][2], rhs.mtx[2][2]);
	}

	inline bool Matrix3f::operator!=(const Matrix3f &rhs) const
	{
		return !(*this == rhs);
	}

	inline Matrix3f &Matrix3f::operator+=(const Matrix3f &rhs)
	{
		mtx[0][0] += rhs.mtx[0][0], mtx[0][1] += rhs.mtx[0][1], mtx[0][2] += rhs.mtx[0][2];
		mtx[1][0] += rhs.mtx[1][0], mtx[1][1] += rhs.mtx[1][1], mtx[1][2] += rhs.mtx[1][2];
		mtx[2][0] += rhs.mtx[2][0], mtx[2][1] += rhs.mtx[2][1], mtx[2][2] += rhs.mtx[2][2];
		return *this;
	}

	inline Matrix3f &Matrix3f::operator-=(const Matrix3f &rhs)
	{
		mtx[0][0] -= rhs.mtx[0][0], mtx[0][1] -= rhs.mtx[0][1], mtx[0][2] -= rhs.mtx[0][2];
		mtx[1][0] -= rhs.mtx[1][0], mtx[1][1] -= rhs.mtx[1][1], mtx[1][2] -= rhs.mtx[1][2];
		mtx[2][0] -= rhs.mtx[2][0], mtx[2][1] -= rhs.mtx[2][1], mtx[2][2] -= rhs.mtx[2][2];
		return *this;
	}

	inline Matrix3f &Matrix3f::operator*=(const Matrix3f &rhs)
	{
		Matrix3f tmp;

		// Row 1.
		tmp.mtx[0][0] = (mtx[0][0] * rhs.mtx[0][0]) + (mtx[0][1] * rhs.mtx[1][0]) + (mtx[0][2] * rhs.mtx[2][0]);
		tmp.mtx[0][1] = (mtx[0][0] * rhs.mtx[0][1]) + (mtx[0][1] * rhs.mtx[1][1]) + (mtx[0][2] * rhs.mtx[2][1]);
		tmp.mtx[0][2] = (mtx[0][0] * rhs.mtx[0][2]) + (mtx[0][1] * rhs.mtx[1][2]) + (mtx[0][2] * rhs.mtx[2][2]);

		// Row 2.
		tmp.mtx[1][0] = (mtx[1][0] * rhs.mtx[0][0]) + (mtx[1][1] * rhs.mtx[1][0]) + (mtx[1][2] * rhs.mtx[2][0]);
		tmp.mtx[1][1] = (mtx[1][0] * rhs.mtx[0][1]) + (mtx[1][1] * rhs.mtx[1][1]) + (mtx[1][2] * rhs.mtx[2][1]);
		tmp.mtx[1][2] = (mtx[1][0] * rhs.mtx[0][2]) + (mtx[1][1] * rhs.mtx[1][2]) + (mtx[1][2] * rhs.mtx[2][2]);

		// Row 3.
		tmp.mtx[2][0] = (mtx[2][0] * rhs.mtx[0][0]) + (mtx[2][1] * rhs.mtx[1][0]) + (mtx[2][2] * rhs.mtx[2][0]);
		tmp.mtx[2][1] = (mtx[2][0] * rhs.mtx[0][1]) + (mtx[2][1] * rhs.mtx[1][1]) + (mtx[2][2] * rhs.mtx[2][1]);
		tmp.mtx[2][2] = (mtx[2][0] * rhs.mtx[0][2]) + (mtx[2][1] * rhs.mtx[1][2]) + (mtx[2][2] * rhs.mtx[2][2]);

		*this = tmp;
		return *this;
	}

	inline Matrix3f &Matrix3f::operator*=(float scalar)
	{
		mtx[0][0] *= scalar, mtx[0][1] *= scalar, mtx[0][2] *= scalar;
		mtx[1][0] *= scalar, mtx[1][1] *= scalar, mtx[1][2] *= scalar;
		mtx[2][0] *= scalar, mtx[2][1] *= scalar, mtx[2][2] *= scalar;
		return *this;
	}

	inline Matrix3f &Matrix3f::operator/=(float scalar)
	{
		mtx[0][0] /= scalar, mtx[0][1] /= scalar, mtx[0][2] /= scalar;
		mtx[1][0] /= scalar, mtx[1][1] /= scalar, mtx[1][2] /= scalar;
		mtx[2][0] /= scalar, mtx[2][1] /= scalar, mtx[2][2] /= scalar;
		return *this;
	}

	inline Matrix3f Matrix3f::operator+(const Matrix3f &rhs) const
	{
		Matrix3f tmp(*this);
		tmp += rhs;
		return tmp;
	}

	inline Matrix3f Matrix3f::operator-(const Matrix3f &rhs) const
	{
		Matrix3f tmp(*this);
		tmp -= rhs;
		return tmp;
	}

	inline Matrix3f Matrix3f::operator*(const Matrix3f &rhs) const
	{
		Matrix3f tmp(*this);
		tmp *= rhs;
		return tmp;
	}

	inline Matrix3f Matrix3f::operator*(float scalar) const
	{
		Matrix3f tmp(*this);
		tmp *= scalar;
		return tmp;
	}

	inline Matrix3f Matrix3f::operator/(float scalar) const
	{
		Matrix3f tmp(*this);
		tmp /= scalar;
		return tmp;
	}

	inline float Matrix3f::determinant() const
	{
		return (mtx[0][0] * (mtx[1][1] * mtx[2][2] - mtx[1][2] * mtx[2][1]))
			- (mtx[0][1] * (mtx[1][0] * mtx[2][2] - mtx[1][2] * mtx[2][0]))
			+ (mtx[0][2] * (mtx[1][0] * mtx[2][1] - mtx[1][1] * mtx[2][0]));
	}

	inline void Matrix3f::fromAxes(const Vector3f &x, const Vector3f &y, const Vector3f &z)
	{
		mtx[0][0] = x.x, mtx[0][1] = x.y, mtx[0][2] = x.z;
		mtx[1][0] = y.x, mtx[1][1] = y.y, mtx[1][2] = y.z;
		mtx[2][0] = z.x, mtx[2][1] = z.y, mtx[2][2] = z.z;
	}

	inline void Matrix3f::fromAxesTransposed(const Vector3f &x, const Vector3f &y, const Vector3f &z)
	{
		mtx[0][0] = x.x, mtx[0][1] = y.x, mtx[0][2] = z.x;
		mtx[1][0] = x.y, mtx[1][1] = y.y, mtx[1][2] = z.y;
		mtx[2][0] = x.z, mtx[2][1] = y.z, mtx[2][2] = z.z;
	}

	inline void Matrix3f::identity()
	{
		mtx[0][0] = 1.0f, mtx[0][1] = 0.0f, mtx[0][2] = 0.0f;
		mtx[1][0] = 0.0f, mtx[1][1] = 1.0f, mtx[1][2] = 0.0f;
		mtx[2][0] = 0.0f, mtx[2][1] = 0.0f, mtx[2][2] = 1.0f;
	}

	inline void Matrix3f::toAxes(Vector3f &x, Vector3f &y, Vector3f &z) const
	{
		x.set(mtx[0][0], mtx[0][1], mtx[0][2]);
		y.set(mtx[1][0], mtx[1][1], mtx[1][2]);
		z.set(mtx[2][0], mtx[2][1], mtx[2][2]);
	}

	inline void Matrix3f::toAxesTransposed(Vector3f &x, Vector3f &y, Vector3f &z) const
	{
		x.set(mtx[0][0], mtx[1][0], mtx[2][0]);
		y.set(mtx[0][1], mtx[1][1], mtx[2][1]);
		z.set(mtx[0][2], mtx[1][2], mtx[2][2]);
	}

	inline Matrix3f Matrix3f::transpose() const
	{
		Matrix3f tmp;

		tmp[0][0] = mtx[0][0], tmp[0][1] = mtx[1][0], tmp[0][2] = mtx[2][0];
		tmp[1][0] = mtx[0][1], tmp[1][1] = mtx[1][1], tmp[1][2] = mtx[2][1];
		tmp[2][0] = mtx[0][2], tmp[2][1] = mtx[1][2], tmp[2][2] = mtx[2][2];

		return tmp;
	}
}