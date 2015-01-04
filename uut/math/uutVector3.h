#pragma once
#include "math/uutMath.h"
#include "container/uutString.h"

namespace uut
{
	class Vector3i;

	/// Two-dimensional vector.
	class UUT_API Vector3
	{
	public:
		/// Construct undefined.
		Vector3();

		/// Copy-construct from another vector.
		Vector3(const Vector3& vector);

		/// Construct from coordinates.
		Vector3(float x, float y, float z);

		explicit Vector3(float val);

		/// Construct from a float array.
		Vector3(const float* data);

		Vector3(const Vector3i& vector);

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
		float Length() const { return sqrtf(LengthSquared()); }
		/// Return squared length.
		float LengthSquared() const { return _x * _x + _y * _y + _z * _z; }
		/// Calculate dot product.
		float DotProduct(const Vector3& rhs) const { return _x * rhs._x + _y * rhs._y + _z * rhs._z; }
		/// Calculate absolute dot product.
		float AbsDotProduct(const Vector3& rhs) const { return Math::Abs(_x * rhs._x) + Math::Abs(_y * rhs._y) + Math::Abs(_z * rhs._z); }
		/// Return absolute vector.
		Vector3 Abs() const { return Vector3(Math::Abs(_x), Math::Abs(_y), Math::Abs(_z)); }
		/// Linear interpolation with another vector.
		Vector3 Lerp(const Vector3& rhs, float t) const { return *this * (1.0f - t) + rhs * t; }
		/// Test for equality with another vector with epsilon.
		bool Equals(const Vector3& rhs) const { return Math::Equals(_x, rhs._x) && Math::Equals(_y, rhs._y) && Math::Equals(_z, rhs._z); }

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
		String ToString() const;

		float _x,  _y, _z;

		/// Zero vector.
		static const Vector3 ZERO;
		/// (-1,0) vector.
		static const Vector3 LEFT;
		/// (1,0) vector.
		static const Vector3 RIGHT;
		/// (0,1) vector.
		static const Vector3 UP;
		/// (0,-1) vector.
		static const Vector3 DOWN;
		/// (1,1) vector.
		static const Vector3 ONE;
	};

	/// Multiply Vector2 with a scalar
	inline Vector3 operator * (float lhs, const Vector3& rhs) { return rhs * lhs; }

	/// Two-dimensional vector with integer values.
	class UUT_API Vector3i
	{
	public:
		/// Construct undefined.
		Vector3i()
		{
		}

		/// Construct from coordinates.
		Vector3i(int x, int y, int z)
			: _x(x), _y(y), _z(z)
		{
		}

		explicit Vector3i(int val)
			: _x(val), _y(val), _z(val)
		{
		}

		/// Construct from an int array.
		Vector3i(const int* data)
			: _x(data[0]), _y(data[1]), _z(data[2])
		{
		}

		/// Copy-construct from another vector.
		Vector3i(const Vector3i& rhs)
			: _x(rhs._x), _y(rhs._y), _z(rhs._z)
		{
		}

		/// Copy-construct from another vector.
		Vector3i(const Vector3& rhs);

		int Area() const { return _x * _y * _z; }

		/// Test for equality with another vector.
		bool operator == (const Vector3i& rhs) const { return _x == rhs._x && _y == rhs._y && _z == rhs._z; }
		/// Test for inequality with another vector.
		bool operator != (const Vector3i& rhs) const { return _x != rhs._x || _y != rhs._y || _z != rhs._z; }
		/// Add a vector.
		Vector3i operator + (const Vector3i& rhs) const { return Vector3i(_x + rhs._x, _y + rhs._y, _z + rhs._z); }
		/// Return negation.
		Vector3i operator - () const { return Vector3i(-_x, -_y, -_z); }
		/// Subtract a vector.
		Vector3i operator - (const Vector3i& rhs) const { return Vector3i(_x - rhs._x, _y - rhs._y, _z - rhs._z); }
		/// Multiply with a scalar.
		Vector3i operator * (int rhs) const { return Vector3i(_x * rhs, _y * rhs, _z * rhs); }
		/// Divide by a scalar.
		Vector3i operator / (int rhs) const { return Vector3i(_x / rhs, _y / rhs, _z / rhs); }

		/// Add-assign a vector.
		Vector3i& operator += (const Vector3i& rhs)
		{
			_x += rhs._x;
			_y += rhs._y;
			_z += rhs._z;
			return *this;
		}

		/// Subtract-assign a vector.
		Vector3i& operator -= (const Vector3i& rhs)
		{
			_x -= rhs._x;
			_y -= rhs._y;
			_z -= rhs._z;
			return *this;
		}

		/// Multiply-assign a scalar.
		Vector3i& operator *= (int rhs)
		{
			_x *= rhs;
			_y *= rhs;
			_z *= rhs;
			return *this;
		}

		/// Divide-assign a scalar.
		Vector3i& operator /= (int rhs)
		{
			_x /= rhs;
			_y /= rhs;
			_z /= rhs;
			return *this;
		}

		/// Return integer data.
		const int* Data() const { return &_x; }
		/// Return as string.
		String ToString() const;

		int _x, _y, _z;

		/// Zero vector.
		static const Vector3i ZERO;
		/// (-1,0) vector.
		static const Vector3i LEFT;
		/// (1,0) vector.
		static const Vector3i RIGHT;
		/// (0,1) vector.
		static const Vector3i UP;
		/// (0,-1) vector.
		static const Vector3i DOWN;
		/// (1,1) vector.
		static const Vector3i ONE;
	};

	/// Multiply IntVector2 with a scalar.
	inline Vector3i operator * (int lhs, const Vector3i& rhs) { return rhs * lhs; }

}
