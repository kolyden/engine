#pragma once
#include "core/uutDefine.h"
#include <math.h>

namespace uut
{
	class Math
	{
	public:
		static const float PI;
		static const float HALF_PI;
		static const float QUARTER_PI;
		static const float TWO_PI;
		static const float EPSILON;

		static const float DEGTORAD;
		static const float DEGTORAD_2;
		static const float RADTODEG;

		template <typename T>
		static T bilerp(const T &a, const T &b, const T &c, const T &d, float u, float v)
		{
			// Performs a bilinear interpolation.
			//  P(u,v) = e + v(f - e)
			//  
			//  where
			//  e = a + u(b - a)
			//  f = c + u(d - c)
			//  u in range [0,1]
			//  v in range [0,1]

			return a * ((1.0f - u) * (1.0f - v))
				+ b * (u * (1.0f - v))
				+ c * (v * (1.0f - u))
				+ d * (u * v);
		}

		static void cartesianToSpherical(float x, float y, float z,
			float &rho, float &phi, float &theta)
		{
			// All angles are in radians.
			// rho = distance from origin O to point P (i.e., length of OP)
			// phi = angle between OP and the XZ plane
			// theta = angle between X-axis and OP projected onto XZ plane

			rho = sqrtf((x * x) + (y * y) + (z * z));
			phi = asinf(y / rho);
			theta = atan2f(z, x);
		}

		static bool closeEnough(float f1, float f2)
		{
			// Determines whether the two floating-point values f1 and f2 are
			// close enough together that they can be considered equal.

			return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
		}

		static float degreesToRadians(float degrees)
		{
			return (degrees * PI) / 180.0f;
		}

		static long floatToLong(float f)
		{
			// Converts a floating point number into an integer.
			// Fractional values are truncated as in ANSI C.
			// About 5 to 6 times faster than a standard typecast to an integer.

			long fpBits = *reinterpret_cast<const long*>(&f);
			long shift = 23 - (((fpBits & 0x7fffffff) >> 23) - 127);
			long result = ((fpBits & 0x7fffff) | (1 << 23)) >> shift;

			result = (result ^ (fpBits >> 31)) - (fpBits >> 31);
			result &= ~((((fpBits & 0x7fffffff) >> 23) - 127) >> 31);

			return result;
		}

		static bool isPower2(int x)
		{
			return ((x > 0) && ((x & (x - 1)) == 0));
		}

		template <typename T>
		static T lerp(const T &a, const T &b, float t)
		{
			// Performs a linear interpolation.
			//  P(t) = (1 - t)a + tb
			//       = a + t(b - a)
			//
			//  where
			//  t in range [0,1]

			return a + (b - a) * t;
		}

		static int nextMultipleOf(int multiple, int value)
		{
			// Returns the closest multiple of value that isn't less than value.

			return multiple * ((value + (multiple - 1)) / multiple);
		}

		static int nextPower2(int x);

		static float radiansToDegrees(float radians)
		{
			return (radians * 180.0f) / PI;
		}

		static float smoothstep(float a, float b, float x)
		{
			// Returns a gradual transition of 'x' from 0 to 1 beginning at
			// threshold 'a' and ending at threshold 'b'.
			//
			// References:
			//  [1] http://www.rendermanacademy.com/docs/smoothstep.htm
			//  [2] http://www.brlcad.org/doxygen/d8/d33/noise_8c-source.html
			//  [3] Natalya Tatarchuk, "Efficient High-Level Shader Development",
			//      Game Developers Conference Europe, August 2003.

			if (x < a)
			{
				return 0.0f;
			}
			else if (x >= b)
			{
				return 1.0f;
			}
			else
			{
				x = (x - a) / (b - a);
				return x * x * (3.0f - 2.0f * x);
			}
		}

		static void sphericalToCartesian(float rho, float phi, float theta,
			float &x, float &y, float &z)
		{
			// All angles are in radians.
			// rho = distance from origin O to point P (i.e., length of OP)
			// phi = angle between OP and the XZ plane
			// theta = angle between X-axis and OP projected onto XZ plane

			x = rho * cosf(phi) * cosf(theta);
			y = rho * sinf(phi);
			z = rho * cosf(phi) * sinf(theta);
		}

		//////////////////////////////////////////////////////////////////////////
		static float ToRad(float angle) { return DEGTORAD * angle; }
		static float ToDeg(float angle) { return RADTODEG * angle; }

		/// Check whether two floating point values are equal within accuracy.
		static bool Equals(float lhs, float rhs) { return lhs + EPSILON >= rhs && lhs - EPSILON <= rhs; }
		/// Linear interpolation between two float values.
		static float Lerp(float lhs, float rhs, float t) { return lhs * (1.0f - t) + rhs * t; }
		/// Return the smaller of two floats.
		static float Min(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }
		/// Return the larger of two floats.
		static float Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }
		/// Return absolute value of a float.
		static float Abs(float value) { return value >= 0.0f ? value : -value; }
		/// Return the sign of a float (-1, 0 or 1.)
		static float Sign(float value) { return value > 0.0f ? 1.0f : (value < 0.0f ? -1.0f : 0.0f); }

		/// Clamp a float to a range.
		static float Clamp(float value, float min, float max)
		{
			if (value < min)
				return min;
			else if (value > max)
				return max;
			else
				return value;
		}

		/// Smoothly damp between values.
		static float SmoothStep(float lhs, float rhs, float t)
		{
			t = Clamp((t - lhs) / (rhs - lhs), 0.0f, 1.0f); // Saturate t
			return t * t * (3.0f - 2.0f * t);
		}

		/// Return sine of an angle in degrees.
		static float Sin(float angle) { return sinf(angle * DEGTORAD); }
		/// Return cosine of an angle in degrees.
		static float Cos(float angle) { return cosf(angle * DEGTORAD); }
		/// Return tangent of an angle in degrees.
		static float Tan(float angle) { return tanf(angle * DEGTORAD); }
		/// Return arc sine in degrees.
		static float Asin(float x) { return RADTODEG * asinf(Clamp(x, -1.0f, 1.0f)); }
		/// Return arc cosine in degrees.
		static float Acos(float x) { return RADTODEG * acosf(Clamp(x, -1.0f, 1.0f)); }
		/// Return arc tangent in degrees.
		static float Atan(float x) { return RADTODEG * atanf(x); }
		/// Return arc tangent of y/x in degrees.
		static float Atan2(float y, float x) { return RADTODEG * atan2f(y, x); }

		/// Return the smaller of two integers.
		static int Min(int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }
		/// Return the larger of two integers.
		static int Max(int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }
		/// Return absolute value of an integer
		static int Abs(int value) { return value >= 0 ? value : -value; }

		/// Clamp an integer to a range.
		static int Clamp(int value, int min, int max)
		{
			if (value < min)
				return min;
			else if (value > max)
				return max;
			else
				return value;
		}

		/// Check whether an unsigned integer is a power of two.
		static bool IsPowerOfTwo(unsigned value)
		{
			if (!value)
				return true;
			while (!(value & 1))
				value >>= 1;
			return value == 1;
		}

		/// Round up to next power of two.
		static unsigned NextPowerOfTwo(unsigned value)
		{
			unsigned ret = 1;
			while (ret < value && ret < 0x80000000)
				ret <<= 1;
			return ret;
		}

		static float Round(float val) { return round(val); }
		static float Ceil(float val) { return ceil(val); }
		static float Floor(float val) { return floor(val); }

		static int RoundToInt(float val) { return (int)Round(val); }
		static int CeilToInt(float val) { return (int)Ceil(val); }
		static int FloorToInt(float val) { return (int)Floor(val); }

		static float Repeat(float t, float length)
		{
			return fmodf(t, length);
		}

		/// Update a hash with the given 8-bit value using the SDBM algorithm.
		static unsigned SDBMHash(unsigned hash, unsigned char c) { return c + (hash << 6) + (hash << 16) - hash; }
	};
}