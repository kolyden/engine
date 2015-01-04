#pragma once
#include "uutVector2.h"

namespace uut
{
	class UUT_API Vector3
	{
	public:
		/// Construct a zero vector.
		Vector3() :
			_x(0.0f),
			_y(0.0f),
			_z(0.0f)
		{
		}

		/// Copy-construct from another vector.
		Vector3(const Vector3& vector) :
			_x(vector._x),
			_y(vector._y),
			_z(vector._z)
		{
		}

		/// Construct from a two-dimensional vector and the Z coordinate.
		Vector3(const Vector2& vector, float z) :
			_x(vector._x),
			_y(vector._y),
			_z(z)
		{
		}

		/// Construct from a two-dimensional vector (for Urho2D).
		Vector3(const Vector2& vector) :
			_x(vector._x),
			_y(vector._y),
			_z(0.0f)
		{
		}

		/// Construct from coordinates.
		Vector3(float x, float y, float z) :
			_x(x),
			_y(y),
			_z(z)
		{
		}

		/// Construct from two-dimensional coordinates (for Urho2D).
		Vector3(float x, float y) :
			_x(x),
			_y(y),
			_z(0.0f)
		{
		}

		/// Construct from a float array.
		Vector3(const float* data) :
			_x(data[0]),
			_y(data[1]),
			_z(data[2])
		{
		}

		/// Assign from another vector.
		Vector3& operator = (const Vector3& rhs)
		{
			_x = rhs._x;
			_y = rhs._y;
			_z = rhs._z;
			return *this;
		}

		/// Test for equality with another vector without epsilon.
		bool operator == (const Vector3& rhs) const { return _x == rhs._x && _y == rhs._y && _z == rhs._z; }
		/// Test for inequality with another vector without epsilon.
		bool operator != (const Vector3& rhs) const { return _x != rhs._x || _y != rhs._y || _z != rhs._z; }
		/// Add a vector.
		Vector3 operator + (const Vector3& rhs) const { return Vector3(_x + rhs._x, _y + rhs._y, _z + rhs._z); }
		/// Return negation.
		Vector3 operator - () const { return Vector3(-_x, -_y, -_z); }
		/// Subtract a vector.
		Vector3 operator - (const Vector3& rhs) const { return Vector3(_x - rhs._x, _y - rhs._y, _z - rhs._z); }
		/// Multiply with a scalar.
		Vector3 operator * (float rhs) const { return Vector3(_x * rhs, _y * rhs, _z * rhs); }
		/// Multiply with a vector.
		Vector3 operator * (const Vector3& rhs) const { return Vector3(_x * rhs._x, _y * rhs._y, _z * rhs._z); }
		/// Divide by a scalar.
		Vector3 operator / (float rhs) const { return Vector3(_x / rhs, _y / rhs, _z / rhs); }
		/// Divide by a vector.
		Vector3 operator / (const Vector3& rhs) const { return Vector3(_x / rhs._x, _y / rhs._y, _z / rhs._z); }

		/// Add-assign a vector.
		Vector3& operator += (const Vector3& rhs)
		{
			_x += rhs._x;
			_y += rhs._y;
			_z += rhs._z;
			return *this;
		}

		/// Subtract-assign a vector.
		Vector3& operator -= (const Vector3& rhs)
		{
			_x -= rhs._x;
			_y -= rhs._y;
			_z -= rhs._z;
			return *this;
		}

		/// Multiply-assign a scalar.
		Vector3& operator *= (float rhs)
		{
			_x *= rhs;
			_y *= rhs;
			_z *= rhs;
			return *this;
		}

		/// Multiply-assign a vector.
		Vector3& operator *= (const Vector3& rhs)
		{
			_x *= rhs._x;
			_y *= rhs._y;
			_z *= rhs._z;
			return *this;
		}

		/// Divide-assign a scalar.
		Vector3& operator /= (float rhs)
		{
			float invRhs = 1.0f / rhs;
			_x *= invRhs;
			_y *= invRhs;
			_z *= invRhs;
			return *this;
		}

		/// Divide-assign a vector.
		Vector3& operator /= (const Vector3& rhs)
		{
			_x /= rhs._x;
			_y /= rhs._y;
			_z /= rhs._z;
			return *this;
		}

		/// Normalize to unit length.
		void Normalize()
		{
			float lenSquared = LengthSquared();
			if (!Math::Equals(lenSquared, 1.0f) && lenSquared > 0.0f)
			{
				float invLen = 1.0f / sqrtf(lenSquared);
				_x *= invLen;
				_y *= invLen;
				_z *= invLen;
			}
		}

		/// Return length.
		float Length() const { return sqrtf(_x * _x + _y * _y + _z * _z); }
		/// Return squared length.
		float LengthSquared() const { return _x * _x + _y * _y + _z * _z; }
		/// Calculate dot product.
		float DotProduct(const Vector3& rhs) const { return _x * rhs._x + _y * rhs._y + _z * rhs._z; }
		/// Calculate absolute dot product.
		float AbsDotProduct(const Vector3& rhs) const { return Math::Abs(_x * rhs._x) + Math::Abs(_y * rhs._y) + Math::Abs(_z * rhs._z); }

		/// Calculate cross product.
		Vector3 CrossProduct(const Vector3& rhs) const
		{
			return Vector3(
				_y * rhs._z - _z * rhs._y,
				_z * rhs._x - _x * rhs._z,
				_x * rhs._y - _y * rhs._x
				);
		}

		/// Return absolute vector.
		Vector3 Abs() const { return Vector3(Math::Abs(_x), Math::Abs(_y), Math::Abs(_z)); }
		/// Linear interpolation with another vector.
		Vector3 Lerp(const Vector3& rhs, float t) const { return *this * (1.0f - t) + rhs * t; }
		/// Test for equality with another vector with epsilon.
		bool Equals(const Vector3& rhs) const { return Math::Equals(_x, rhs._x) && Math::Equals(_y, rhs._y) && Math::Equals(_z, rhs._z); }
		/// Returns the angle between this vector and another vector in degrees.
		float Angle(const Vector3& rhs) const { return Math::Acos(DotProduct(rhs) / (Length() * rhs.Length())); }
		/// Return whether is NaN.
// 		bool IsNaN() const { return Urho3D::IsNaN(x_) || Math::IsNaN(y_) || Math::IsNaN(z_); }

		/// Return normalized to unit length.
		Vector3 Normalized() const
		{
			float lenSquared = LengthSquared();
			if (!Math::Equals(lenSquared, 1.0f) && lenSquared > 0.0f)
			{
				float invLen = 1.0f / sqrtf(lenSquared);
				return *this * invLen;
			}
			else
				return *this;
		}

		/// Return float data.
		const float* Data() const { return &_x; }
		/// Return as string.
// 		String ToString() const;

		/// coordinates
		float _x, _y, _z;

		/// Zero vector.
		static const Vector3 ZERO;
		/// (-1,0,0) vector.
		static const Vector3 LEFT;
		/// (1,0,0) vector.
		static const Vector3 RIGHT;
		/// (0,1,0) vector.
		static const Vector3 UP;
		/// (0,-1,0) vector.
		static const Vector3 DOWN;
		/// (0,0,1) vector.
		static const Vector3 FORWARD;
		/// (0,0,-1) vector.
		static const Vector3 BACK;
		/// (1,1,1) vector.
		static const Vector3 ONE;
	};

	/// Multiply Vector3 with a scalar.
	inline Vector3 operator * (float lhs, const Vector3& rhs) { return rhs * lhs; }

}
