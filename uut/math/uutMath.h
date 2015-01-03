#pragma once
#include "core/uutDefine.h"
#include <math.h>

namespace uut
{
	namespace Math
	{
		static const float PI = 3.14159265358979323846264338327950288f;
		static const float HALF_PI = PI * 0.5f;

		static const float EPSILON = 0.000001f;
		static const float DEGTORAD = (float)PI / 180.0f;
		static const float DEGTORAD_2 = (float)PI / 360.0f; // M_DEGTORAD / 2.f
		static const float RADTODEG = 1.0f / DEGTORAD;

		/// Check whether two floating point values are equal within accuracy.
		inline bool Equals(float lhs, float rhs) { return lhs + EPSILON >= rhs && lhs - EPSILON <= rhs; }
		/// Linear interpolation between two float values.
		inline float Lerp(float lhs, float rhs, float t) { return lhs * (1.0f - t) + rhs * t; }
		/// Return the smaller of two floats.
		inline float Min(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }
		/// Return the larger of two floats.
		inline float Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }
		/// Return absolute value of a float.
		inline float Abs(float value) { return value >= 0.0f ? value : -value; }
		/// Return the sign of a float (-1, 0 or 1.)
		inline float Sign(float value) { return value > 0.0f ? 1.0f : (value < 0.0f ? -1.0f : 0.0f); }

		/// Clamp a float to a range.
		inline float Clamp(float value, float min, float max)
		{
			if (value < min)
				return min;
			else if (value > max)
				return max;
			else
				return value;
		}

		/// Smoothly damp between values.
		inline float SmoothStep(float lhs, float rhs, float t)
		{
			t = Clamp((t - lhs) / (rhs - lhs), 0.0f, 1.0f); // Saturate t
			return t * t * (3.0f - 2.0f * t);
		}

		/// Return sine of an angle in degrees.
		inline float Sin(float angle) { return sinf(angle * DEGTORAD); }
		/// Return cosine of an angle in degrees.
		inline float Cos(float angle) { return cosf(angle * DEGTORAD); }
		/// Return tangent of an angle in degrees.
		inline float Tan(float angle) { return tanf(angle * DEGTORAD); }
		/// Return arc sine in degrees.
		inline float Asin(float x) { return RADTODEG * asinf(Clamp(x, -1.0f, 1.0f)); }
		/// Return arc cosine in degrees.
		inline float Acos(float x) { return RADTODEG * acosf(Clamp(x, -1.0f, 1.0f)); }
		/// Return arc tangent in degrees.
		inline float Atan(float x) { return RADTODEG * atanf(x); }
		/// Return arc tangent of y/x in degrees.
		inline float Atan2(float y, float x) { return RADTODEG * atan2f(y, x); }

		/// Return the smaller of two integers.
		inline int Min(int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }
		/// Return the larger of two integers.
		inline int Max(int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }
		/// Return absolute value of an integer
		inline int Abs(int value) { return value >= 0 ? value : -value; }

		/// Clamp an integer to a range.
		inline int Clamp(int value, int min, int max)
		{
			if (value < min)
				return min;
			else if (value > max)
				return max;
			else
				return value;
		}

		/// Check whether an unsigned integer is a power of two.
		inline bool IsPowerOfTwo(unsigned value)
		{
			if (!value)
				return true;
			while (!(value & 1))
				value >>= 1;
			return value == 1;
		}

		/// Round up to next power of two.
		inline unsigned NextPowerOfTwo(unsigned value)
		{
			unsigned ret = 1;
			while (ret < value && ret < 0x80000000)
				ret <<= 1;
			return ret;
		}

		inline float Round(float val) { return round(val); }
		inline float Ceil(float val) { return ceil(val); }
		inline float Floor(float val) { return floor(val); }

		inline int RoundToInt(float val) { return (int)Round(val); }
		inline int CeilToInt(float val) { return (int)Ceil(val); }
		inline int FloorToInt(float val) { return (int)Floor(val); }

		inline float Repeat(float t, float length)
		{
			return fmodf(t, length);
		}

		/// Update a hash with the given 8-bit value using the SDBM algorithm.
		inline unsigned SDBMHash(unsigned hash, unsigned char c) { return c + (hash << 6) + (hash << 16) - hash; }
	}
}