#pragma once
#include "math/uutMath.h"
#include "container/uutString.h"

namespace uut
{
	class Vector2i;

    /// Two-dimensional vector.
    class UUT_API Vector2
    {
    public:
        /// Construct undefined.
        Vector2()
        {
        }

        /// Copy-construct from another vector.
        Vector2(const Vector2& vector) :
            _x(vector._x),
            _y(vector._y)
        {
        }

        /// Construct from coordinates.
        Vector2(float x, float y)
            : _x(x), _y(y)
        {
        }

        explicit Vector2(float val)
            : _x(val), _y(val)
        {
        }

        /// Construct from a float array.
        Vector2(const float* data)
            : _x(data[0]), _y(data[1])
        {
        }

		Vector2(const Vector2i& vector);

        /// Assign from another vector.
        Vector2& operator = (const Vector2& rhs)
        {
            _x = rhs._x;
            _y = rhs._y;
            return *this;
        }

        /// Test for equality with another vector without epsilon.
        bool operator == (const Vector2& rhs) const { return _x == rhs._x && _y == rhs._y; }
        /// Test for inequality with another vector without epsilon.
        bool operator != (const Vector2& rhs) const { return _x != rhs._x || _y != rhs._y; }
        /// Add a vector.
        Vector2 operator + (const Vector2& rhs) const { return Vector2(_x + rhs._x, _y + rhs._y); }
        /// Return negation.
        Vector2 operator - () const { return Vector2(-_x, -_y); }
        /// Subtract a vector.
        Vector2 operator - (const Vector2& rhs) const { return Vector2(_x - rhs._x, _y - rhs._y); }
        /// Multiply with a scalar.
        Vector2 operator * (float rhs) const { return Vector2(_x * rhs, _y * rhs); }
        /// Multiply with a vector.
        Vector2 operator * (const Vector2& rhs) const { return Vector2(_x * rhs._x, _y * rhs._y); }
        /// Divide by a scalar.
        Vector2 operator / (float rhs) const { return Vector2(_x / rhs, _y / rhs); }
        /// Divide by a vector.
        Vector2 operator / (const Vector2& rhs) const { return Vector2(_x / rhs._x, _y / rhs._y); }

        /// Add-assign a vector.
        Vector2& operator += (const Vector2& rhs)
        {
            _x += rhs._x;
            _y += rhs._y;
            return *this;
        }

        /// Subtract-assign a vector.
        Vector2& operator -= (const Vector2& rhs)
        {
            _x -= rhs._x;
            _y -= rhs._y;
            return *this;
        }

        /// Multiply-assign a scalar.
        Vector2& operator *= (float rhs)
        {
            _x *= rhs;
            _y *= rhs;
            return *this;
        }

        /// Multiply-assign a vector.
        Vector2& operator *= (const Vector2& rhs)
        {
            _x *= rhs._x;
            _y *= rhs._y;
            return *this;
        }

        /// Divide-assign a scalar.
        Vector2& operator /= (float rhs)
        {
            float invRhs = 1.0f / rhs;
            _x *= invRhs;
            _y *= invRhs;
            return *this;
        }

        /// Divide-assign a vector.
        Vector2& operator /= (const Vector2& rhs)
        {
            _x /= rhs._x;
            _y /= rhs._y;
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
            }
        }

        /// Return length.
        float Length() const { return sqrtf(_x * _x + _y * _y); }
        /// Return squared length.
        float LengthSquared() const { return _x * _x + _y * _y; }
        /// Calculate dot product.
        float DotProduct(const Vector2& rhs) const { return _x * rhs._x + _y * rhs._y; }
        /// Calculate absolute dot product.
		float AbsDotProduct(const Vector2& rhs) const { return Math::Abs(_x * rhs._x) + Math::Abs(_y * rhs._y); }
        /// Return absolute vector.
		Vector2 Abs() const { return Vector2(Math::Abs(_x), Math::Abs(_y)); }
        /// Linear interpolation with another vector.
        Vector2 Lerp(const Vector2& rhs, float t) const { return *this * (1.0f - t) + rhs * t; }
        /// Test for equality with another vector with epsilon.
		bool Equals(const Vector2& rhs) const { return Math::Equals(_x, rhs._x) && Math::Equals(_y, rhs._y); }

        /// Return normalized to unit length.
        Vector2 Normalized() const
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

        /// X coordinate.
        float _x;
        /// Y coordinate.
        float _y;

        /// Zero vector.
        static const Vector2 ZERO;
        /// (-1,0) vector.
        static const Vector2 LEFT;
        /// (1,0) vector.
        static const Vector2 RIGHT;
        /// (0,1) vector.
        static const Vector2 UP;
        /// (0,-1) vector.
        static const Vector2 DOWN;
        /// (1,1) vector.
        static const Vector2 ONE;
    };

    /// Multiply Vector2 with a scalar
    inline Vector2 operator * (float lhs, const Vector2& rhs) { return rhs * lhs; }

    /// Two-dimensional vector with integer values.
    class UUT_API Vector2i
    {
    public:
        /// Construct undefined.
        Vector2i()
        {
        }

        /// Construct from coordinates.
        Vector2i(int x, int y)
            : _x(x), _y(y)
        {
        }

        explicit Vector2i(int val)
            : _x(val), _y(val)
        {
        }

        /// Construct from an int array.
        Vector2i(const int* data)
            : _x(data[0]), _y(data[1])
        {
        }

        /// Copy-construct from another vector.
        Vector2i(const Vector2i& rhs)
            : _x(rhs._x), _y(rhs._y)
        {
        }

		/// Copy-construct from another vector.
		Vector2i(const Vector2& rhs);

        int Area() const { return _x * _y; }

        /// Test for equality with another vector.
        bool operator == (const Vector2i& rhs) const { return _x == rhs._x && _y == rhs._y; }
        /// Test for inequality with another vector.
        bool operator != (const Vector2i& rhs) const { return _x != rhs._x || _y != rhs._y; }
        /// Add a vector.
        Vector2i operator + (const Vector2i& rhs) const { return Vector2i(_x + rhs._x, _y + rhs._y); }
        /// Return negation.
        Vector2i operator - () const { return Vector2i(-_x, -_y); }
        /// Subtract a vector.
        Vector2i operator - (const Vector2i& rhs) const { return Vector2i(_x - rhs._x, _y - rhs._y); }
        /// Multiply with a scalar.
        Vector2i operator * (int rhs) const { return Vector2i(_x * rhs, _y * rhs); }
        /// Divide by a scalar.
        Vector2i operator / (int rhs) const { return Vector2i(_x / rhs, _y / rhs); }

        /// Add-assign a vector.
        Vector2i& operator += (const Vector2i& rhs)
        {
            _x += rhs._x;
            _y += rhs._y;
            return *this;
        }

        /// Subtract-assign a vector.
        Vector2i& operator -= (const Vector2i& rhs)
        {
            _x -= rhs._x;
            _y -= rhs._y;
            return *this;
        }

        /// Multiply-assign a scalar.
        Vector2i& operator *= (int rhs)
        {
            _x *= rhs;
            _y *= rhs;
            return *this;
        }

        /// Divide-assign a scalar.
        Vector2i& operator /= (int rhs)
        {
            _x /= rhs;
            _y /= rhs;
            return *this;
        }

        /// Return integer data.
        const int* Data() const { return &_x; }
        /// Return as string.
        String ToString() const;

        /// X coordinate.
        int _x;
        /// Y coordinate.
        int _y;

		/// Zero vector.
		static const Vector2i ZERO;
		/// (-1,0) vector.
		static const Vector2i LEFT;
		/// (1,0) vector.
		static const Vector2i RIGHT;
		/// (0,1) vector.
		static const Vector2i UP;
		/// (0,-1) vector.
		static const Vector2i DOWN;
		/// (1,1) vector.
		static const Vector2i ONE;
	};

    /// Multiply IntVector2 with a scalar.
    inline Vector2i operator * (int lhs, const Vector2i& rhs) { return rhs * lhs; }

}
